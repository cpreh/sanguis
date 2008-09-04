#include "../../media_path.hpp"
#include "factory.hpp"
#include <sge/fstream.hpp>
#include <sge/sstream.hpp>
#include <sge/iostream.hpp>
#include <sge/string.hpp>
#include <sge/renderer/device.hpp>
#include <sge/image/loader.hpp>
#include <sge/texture/default_creator_impl.hpp>
#include <sge/texture/no_fragmented.hpp>
#include <sge/texture/manager.hpp>
#include <sge/texture/util.hpp>
#include <sge/time/millisecond.hpp>
#include <boost/filesystem.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/optional.hpp>
#include <map>
#include <utility>
#include <string>
#include <iomanip>
#include <iosfwd>
#include <ostream>
#include <map>
#include <limits>
#include <cstddef>

//#include <sge/texture/rect_fragmented.hpp>

namespace
{

struct environment
{
	const sge::renderer::device_ptr rend;
	const sge::image::loader_ptr il;
	sge::texture::manager texman;
	std::map<sge::string, sge::string> textures;

	environment(sge::image::loader_ptr, sge::renderer::device_ptr);
	void load_textures();
	sge::texture::part_ptr const load_texture(const sanguis::load::resource::identifier_type &);
	sge::texture::part_ptr const load_texture_inner(const sge::path &);
	const sge::sprite::animation_series load_animation(
		sge::path const&);
};

environment::environment(const sge::image::loader_ptr il,const sge::renderer::device_ptr r) 
: rend(r),
  il(il),
  texman(
  	rend,
	sge::texture::default_creator<sge::texture::no_fragmented>(
	//sge::texture::default_creator<sge::texture::rect_fragmented>(
		rend,
		sge::renderer::linear_filter))
{
	load_textures();
}

const sge::sprite::animation_series
environment::load_animation(
	sge::path const& dir)
{
	if (!boost::filesystem::exists(dir) || !boost::filesystem::is_directory(dir))
		throw sge::exception(SGE_TEXT("directory for animation \"")+dir.string()+SGE_TEXT("\" doesn't exist"));

	const sge::path framesfile = dir/SGE_TEXT("frames");

	// look for frames file inside directory
	if (!boost::filesystem::exists(framesfile) || !boost::filesystem::is_regular(framesfile))
	{
		// there is no animation here so just take the first image you can find
		for(sge::directory_iterator it(dir), end; it != end; ++it)
		{
			if(boost::filesystem::is_directory(*it))
				continue;
			sge::sprite::animation_series ret;
			ret.push_back(
				sge::sprite::animation_entity(
					sge::time::millisecond(
						static_cast<sge::time::unit>(1)),
					load_texture_inner(*it)));
			return ret; // TODO: can we do this with boost::assign?
		}
		throw sge::exception(dir.string() + " is empty!");
	}

	// and parse line by line
	sge::ifstream file(framesfile);
	if (!file.is_open())
		throw sge::exception(SGE_TEXT("error opening file \"")+framesfile.string()+SGE_TEXT("\""));
	
	// read first line, determine if it has constant frame time
	sge::string line;
	if (!std::getline(file,line))
		throw sge::exception(SGE_TEXT("unexpected end of file \"")+framesfile.string());

	boost::optional<sge::time::millisecond> const_delay;
	if (boost::algorithm::starts_with(line,SGE_TEXT("frame_length ")))
		const_delay.reset(
			sge::time::millisecond(
				boost::lexical_cast<sge::time::unit>(
					line.substr(sge::string("frame_length ").length()))));
	else
		file.seekg(0,std::ios_base::beg);
	
	sge::sprite::animation_series anim;

	unsigned lineno = const_delay ? 2 : 1;
	while (std::getline(file,line))
	{
		boost::algorithm::trim(line);

		if (line.empty())
			continue;

		sge::time::millisecond delay(sge::su(0));
		sge::string filename = line;

		if (!const_delay)
		{
			sge::istringstream ss(line);
			sge::time::unit temp_delay;
			ss >> temp_delay >> std::ws;
			if (!ss)
				throw sge::exception(SGE_TEXT("invalid line ")+boost::lexical_cast<sge::string>(lineno)+SGE_TEXT(" in animation ")+dir.string());
			filename = ss.str().substr(ss.tellg());
			delay = sge::time::millisecond(temp_delay);
		}
		else
		{
			delay = *const_delay;
		}

		anim.push_back(
			sge::sprite::animation_entity(
				delay,
				load_texture_inner(dir/filename)));
		++lineno;
	}
		
	return anim;
}

sge::texture::part_ptr const environment::load_texture_inner(const sge::path& p)
{
	return sge::texture::add(texman,il->load_image(p));
}

sge::texture::part_ptr const environment::load_texture(const sanguis::load::resource::identifier_type& id)
{
	if (textures.find(id) == textures.end())
		throw sge::exception(SGE_TEXT("no texture for id \"")+id+SGE_TEXT("\" found"));
	return load_texture_inner(sanguis::media_path()/textures[id]);
}

void environment::load_textures()
{
	// look for .tex files
	for (boost::filesystem::basic_directory_iterator<sge::path> i(sanguis::media_path()),end; i != end; ++i)
	{
		const sge::path &p = i->path();
		if (!boost::filesystem::is_regular(p) || !boost::algorithm::ends_with(p.leaf(),SGE_TEXT(".tex")))
			continue;
		
		// and parse line by line
		sge::ifstream file(p);
		if (!file.is_open())
			throw sge::exception(SGE_TEXT("error opening id file \"")+p.string()+SGE_TEXT("\""));

		std::streamsize line_num(0);
		sge::string line;
		while (std::getline(file,line))
		{
			++line_num;

			boost::algorithm::trim(line);

			if (line.empty())
				continue;

			const sge::string::size_type equal = line.find(SGE_TEXT("="));
			if(equal == sge::string::npos)
			{
				sge::cerr << SGE_TEXT("Error in .id file \")")
				          << p.string()
				          << SGE_TEXT("\" in line ")
					  << line_num
					  << SGE_TEXT("!\n");
				continue;
			}
			textures[line.substr(0,equal)] = line.substr(equal+1);
		}
	}
}

template<typename Key, typename Mapped, typename Comp, typename Alloc, typename Fun>
const Mapped& map_get_or_create(std::map<Key, Mapped, Comp, Alloc>& map, const Key& key, const Fun& creator)
{
	const typename std::map<Key, Mapped, Comp, Alloc>::const_iterator it = map.find(key);
	return it != map.end() ? it->second : map.insert(std::make_pair(key, creator(key))).first->second;
}

typedef std::map<sanguis::load::resource::identifier_type,
                 sge::texture::part_ptr>
	texture_map;
texture_map textures;

typedef std::map<sge::path,
                 sge::sprite::animation_series>
	animation_map;
animation_map animations;

const sge::sprite::animation_series
load_animation(
	sge::path const&);

const sge::texture::part_ptr
load_texture(const sanguis::load::resource::identifier_type&);

environment *env = 0;
std::size_t refcount = 0;

}

const sge::sprite::animation_series
sanguis::load::resource::animation(sge::path const& path)
{
	return map_get_or_create(animations, path, load_animation);
}

const sge::texture::part_ptr
sanguis::load::resource::texture(const identifier_type& id)
{
	return map_get_or_create(textures, id, load_texture);
}

sanguis::load::resource::connection::connection(const sge::image::loader_ptr pm,const sge::renderer::device_ptr rend) 
{
	if (refcount++ == 0)
		env = new environment(pm,rend);
}

sanguis::load::resource::connection::~connection() 
{ 
	if (--refcount == 0)
	{
		animations.clear();
		textures.clear(); // TODO: this should really be part of environment
		delete env;
		env = 0;
	}
}

namespace
{

void check_env()
{
	if (!env)
		throw sge::exception(SGE_TEXT("no resource connection found"));
}

const sge::texture::part_ptr
load_texture(const sanguis::load::resource::identifier_type& id)
{
	check_env();
	return env->load_texture(id);
}

const sge::sprite::animation_series
load_animation(
	sge::path const& p)
{
	check_env();
	return env->load_animation(p);
}

}
