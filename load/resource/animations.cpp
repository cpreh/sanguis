#include "animations.hpp"
#include "textures.hpp"
#include "map_get_or_create.hpp"
#include "../log.hpp"
#include "../../exception.hpp"
#include <sge/time/millisecond.hpp>
#include <sge/time/resolution.hpp>
#include <sge/log/headers.hpp>
#include <sge/filesystem/exists.hpp>
#include <sge/filesystem/is_directory.hpp>
#include <sge/filesystem/is_regular.hpp>
#include <sge/filesystem/next_file.hpp>
#include <sge/filesystem/first_file.hpp>
#include <sge/lexical_cast.hpp>
#include <sge/optional_impl.hpp>
#include <sge/fstream.hpp>
#include <sge/istringstream.hpp>
#include <sge/text.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <tr1/functional>

sge::sprite::animation::series const
sanguis::load::resource::animations::load(
	sge::filesystem::path const &dir) const
{
	return map_get_or_create(
		animations_,
		dir, 
		std::tr1::bind(
			&animations::do_load,
			this,
			std::tr1::placeholders::_1
		)
	);
}

sge::sprite::animation::series const
sanguis::load::resource::animations::do_load(
	sge::filesystem::path const &dir) const
{
	if (!sge::filesystem::exists(dir) || !sge::filesystem::is_directory(dir))
		throw exception(
			SGE_TEXT("directory for animation \"")
			+ dir.string()
			+ SGE_TEXT("\" doesn't exist")
		);

	sge::filesystem::path const framesfile = dir / SGE_TEXT("frames");

	// look for frames file inside directory
	if (!sge::filesystem::exists(framesfile) || !sge::filesystem::is_regular(framesfile))
		return load_without_frames_file(dir);
	//
	// and parse line by line
	sge::ifstream file(framesfile);
	if (!file.is_open())
		throw exception(
			SGE_TEXT("error opening file \"")
			+ framesfile.string()
			+ SGE_TEXT("\""));
	
	// read first line, determine if it has constant frame time
	sge::string line;
	if (!std::getline(file,line))
		throw exception(
			SGE_TEXT("unexpected end of file \"")
			+ framesfile.string());

	sge::optional<
		sge::time::resolution
	> const_delay;

	if (boost::algorithm::starts_with(line,SGE_TEXT("frame_length ")))
		const_delay =
			sge::time::millisecond(
				sge::lexical_cast<
					sge::time::unit
				>(
					line.substr(
						sge::string(
							SGE_TEXT("frame_length ")
						)
						.length()
					)
				)
			);
	else
		file.seekg(0, std::ios_base::beg);
	
	sge::sprite::animation::series anim;

	unsigned lineno = const_delay ? 2 : 1;
	while (std::getline(file,line))
	{
		boost::algorithm::trim(line);

		if (line.empty())
			continue;

		sge::time::resolution delay(0);
		sge::string filename = line;

		if (!const_delay)
		{
			sge::istringstream ss(line);
			sge::time::unit temp_delay;
			ss >> temp_delay >> std::ws;
			if (!ss)
				throw exception(
					SGE_TEXT("invalid line ")
					+ sge::lexical_cast<sge::string>(lineno)
					+ SGE_TEXT(" in animation ")
					+ dir.string());
			filename = ss.str().substr(ss.tellg());
			delay = sge::time::millisecond(temp_delay);
		}
		else
		{
			delay = *const_delay;
		}

		anim.push_back(
			sge::sprite::animation::entity(
				delay,
				load_texture(
					dir / filename
				)
			)
		);

		++lineno;
	}
		
	return anim;
}

sge::texture::const_part_ptr const
sanguis::load::resource::animations::load_texture(
	sge::filesystem::path const &p) const
{
	return textures_.do_load_inner(p);	
}

sge::sprite::animation::series const
sanguis::load::resource::animations::load_without_frames_file(
	sge::filesystem::path const &dir) const
{
	sge::filesystem::directory_iterator const first_file(
		sge::filesystem::first_file(
			dir));
	
	if(first_file == sge::filesystem::directory_iterator())
		throw exception(dir.string() + SGE_TEXT(" is empty!"));
	
	sge::filesystem::path const first_path(
		*first_file);

	if(sge::filesystem::next_file(first_file) != sge::filesystem::directory_iterator())
		SGE_LOG_WARNING(
			log(),
			sge::log::_
				<< SGE_TEXT("No frames file found in \"")
				<< dir
				<< SGE_TEXT("\" although there is more than one file!")
				<< SGE_TEXT(" Just taking the first image."));

	sge::sprite::animation::series ret;
	ret.push_back(
		sge::sprite::animation::entity(
			sge::time::millisecond(
				static_cast<sge::time::unit>(1)),
			load_texture(first_path)
		)
	);
	return ret; // TODO: can we do this with boost::assign?
}


sanguis::load::resource::animations::animations(
	textures &textures_)
:
	textures_(textures_)
{}
