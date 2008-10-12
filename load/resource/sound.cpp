#include "environment.hpp"
#include "../log.hpp"
#include "../../exception.hpp"
#include "map_get_or_create.hpp"
#include <sge/log/headers.hpp>
#include <sge/audio/player.hpp>
#include <sge/audio/pool.hpp>
#include <sge/fstream.hpp>
#include <boost/bind.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/convenience.hpp>
#include <istream>
#include <ostream>

sanguis::load::sound_collection const &
sanguis::load::resource::environment::load_sound(
	sge::path const &dir)
{
	return map_get_or_create(
		sounds, 
		dir, 
		boost::bind(
			&environment::do_load_sound,
			this,
			_1));
}

sanguis::load::sound_collection const
sanguis::load::resource::environment::do_load_sound(
	sge::path const &dir)
{
	// a missing directory is valid
	if (!boost::filesystem::exists(dir) || 
	    !boost::filesystem::is_directory(dir))
		return sound_collection(
			sound_container(),
			sge::su(0));

	sound_container container;
	sge::space_unit probability(sge::su(1));

	for(sge::directory_iterator it(dir), end; it != end; ++it)
	{
		if(boost::filesystem::is_directory(*it))
		{ // needed because SGE_LOG_WARNING has its own if()
			SGE_LOG_WARNING(
				log(),
				sge::log::_1
					<< *it
					<< SGE_TEXT(" is a directory!"));
			continue;
		}

		if(boost::filesystem::basename(*it) == SGE_TEXT("probability"))
		{
			sge::ifstream file(*it);
			if(!file.is_open() || !(file >> probability))
			{
				SGE_LOG_WARNING(
					log(),
					sge::log::_1
						<< SGE_TEXT("Failed reading probability file in \"")
						<< boost::filesystem::basename(dir)
						<< SGE_TEXT("\"!"));
			}
			else
				SGE_LOG_DEBUG(
					log(),
					sge::log::_1
						<< SGE_TEXT("Loaded sound probability ")
						<< probability
						<< SGE_TEXT(" in \"")
						<< boost::filesystem::basename(dir)
						<< SGE_TEXT("\"!"));
			
			continue;
		}
		container.push_back(ml.load(*it));
	}

	return sound_collection(
		container,
		probability);
}

sge::audio::sound_ptr const
sanguis::load::resource::environment::make_sound(
	sge::audio::file_ptr const snd) const
{
	sge::audio::sound_ptr const ss = player->create_nonstream_sound(
		snd);
	sound_pool->add(ss);
	return ss;
}
