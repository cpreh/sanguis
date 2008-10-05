#include "environment.hpp"
#include <boost/bind.hpp>

namespace
{
template<typename Key, typename Mapped, typename Comp, typename Alloc, typename Fun>
Mapped const& map_get_or_create(std::map<Key, Mapped, Comp, Alloc>& map, Key const& key, Fun const& creator)
{
	const typename std::map<Key, Mapped, Comp, Alloc>::const_iterator it = map.find(key);
	return it != map.end() ? it->second : map.insert(std::make_pair(key, creator(key))).first->second;
}
}

sanguis::load::resource::environment::environment(
	sge::image::loader_ptr const il,
	sge::renderer::device_ptr const r,
	sge::audio::multi_loader const ml,
	sge::audio::player_ptr const player) 
: rend(r),
  il(il),
	ml(ml),
	player(player),
  texman(
  	rend,
	sge::texture::default_creator<sge::texture::no_fragmented>(
		rend,
		sge::renderer::linear_filter))
{
	load_textures();
}

sge::sprite::animation_series const
sanguis::load::resource::environment::load_animation(
	sge::path const& dir)
{
	return map_get_or_create(animations, path, boost::bind(&enviroment::do_load_animation,this));
}

sge::sprite::animation_series const
sanguis::load::resource::environment::do_load_animation(
	sge::path const& dir)
{
	if (!boost::filesystem::exists(dir) || !boost::filesystem::is_directory(dir))
		throw exception(SGE_TEXT("directory for animation \"")+dir.string()+SGE_TEXT("\" doesn't exist"));

	const sge::path framesfile = dir / SGE_TEXT("frames");

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
					do_load_texture_inner(*it)));
			return ret; // TODO: can we do this with boost::assign?
		}
		throw exception(dir.string() + SGE_TEXT(" is empty!"));
	}

	// and parse line by line
	sge::ifstream file(framesfile);
	if (!file.is_open())
		throw exception(SGE_TEXT("error opening file \"")+framesfile.string()+SGE_TEXT("\""));
	
	// read first line, determine if it has constant frame time
	sge::string line;
	if (!std::getline(file,line))
		throw exception(SGE_TEXT("unexpected end of file \"")+framesfile.string());

	boost::optional<sge::time::millisecond> const_delay;
	if (boost::algorithm::starts_with(line,SGE_TEXT("frame_length ")))
		const_delay.reset(
			sge::time::millisecond(
				boost::lexical_cast<sge::time::unit>(
					line.substr(sge::string(SGE_TEXT("frame_length ")).length()))));
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
				throw exception(SGE_TEXT("invalid line ")+boost::lexical_cast<sge::string>(lineno)+SGE_TEXT(" in animation ")+dir.string());
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
				do_load_texture_inner(dir/filename)));
		++lineno;
	}
		
	return anim;
}

sge::texture::part_ptr const sanguis::load::resource::environment::do_load_texture_inner(
	sge::path const &p)
{
	return sge::texture::add(texman,il->load_image(p));
}

sge::audio::sound_ptr const sanguis::load::resource::environment::load_sound(
	sge::path const &dir)
{
	return map_get_or_create(sounds, p, boost::bind(&environment::do_load_sound,this));
}

sge::audio::sound_ptr const sanguis::load::resource::environment::do_load_sound(
	sge::path const &dir)
{
	return sge::audio::sound_ptr();
	//if (!boost::filesystem::exists(dir) || !boost::filesystem::is_directory(dir))
	//	throw exception(SGE_TEXT("directory for sound \"")+dir.string()+SGE_TEXT("\" doesn't exist"));
}

sge::texture::part_ptr const sanguis::load::resource::environment::load_texture(
	sanguis::load::resource::identifier_type const&id)
{
	return map_get_or_create(textures, id, boost::bind(&environment::do_load_texture,this));
}

sge::texture::part_ptr const sanguis::load::resource::environment::do_load_texture(
	sanguis::load::resource::identifier_type const&id)
{
	if (textures.find(id) == textures.end())
		throw exception(SGE_TEXT("no texture for id \"")+id+SGE_TEXT("\" found"));
	return do_load_texture_inner(sanguis::media_path()/textures[id]);
}

void sanguis::load::resource::environment::load_textures()
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
			throw exception(SGE_TEXT("error opening id file \"")+p.string()+SGE_TEXT("\""));

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
				SGE_LOG_WARNING(
					sanguis::load::log(),
					sge::log::_1
						<< SGE_TEXT("Error in .id file \")")
						<< p.string()
						<< SGE_TEXT("\" in line ")
						<< line_num
						<< SGE_TEXT('!'));
				continue;
			}
			textures[line.substr(0,equal)] = line.substr(equal+1);
		}
	}
}
