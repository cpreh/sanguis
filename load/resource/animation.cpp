#include "environment.hpp"
#include "../../exception.hpp"
#include <sge/time/millisecond.hpp>
#include <sge/fstream.hpp>
#include <sge/sstream.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/optional.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/algorithm/string/predicate.hpp>

sge::sprite::animation_series const
sanguis::load::resource::environment::do_load_animation(
	sge::path const& dir)
{
	if (!boost::filesystem::exists(dir) || !boost::filesystem::is_directory(dir))
		throw exception(SGE_TEXT("directory for animation \"")+dir.string()+SGE_TEXT("\" doesn't exist"));

	sge::path const framesfile = dir / SGE_TEXT("frames");

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
