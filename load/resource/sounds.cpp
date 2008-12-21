#include "sounds.hpp"
#include "map_get_or_create.hpp"
#include "../sound_collection.hpp"
#include "../log.hpp"
#include "../../exception.hpp"
#include <sge/log/headers.hpp>
#include <sge/audio/player.hpp>
#include <sge/audio/pool.hpp>
#include <sge/audio/multi_loader.hpp>
#include <sge/fstream.hpp>
#include <sge/text.hpp>
#include <boost/bind.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/convenience.hpp>
#include <istream>
#include <ostream>

sanguis::load::sound_collection const &
sanguis::load::resource::sounds::load(
	sge::path const &dir)
{
	return map_get_or_create(
		sounds_,
		dir, 
		boost::bind(
			&sounds::do_load,
			this,
			_1));
}

sanguis::load::resource::sounds::~sounds()
{}

sanguis::load::sound_collection const
sanguis::load::resource::sounds::do_load(
	sge::path const &dir)
{
	// a missing directory is valid
	if (!boost::filesystem::exists(dir) || 
	    !boost::filesystem::is_directory(dir))
		return sound_collection(
			sound_container(),
			static_cast<probability_type>(0));

	sound_container container;
	probability_type probability(
		static_cast<probability_type>(1));

	for(sge::directory_iterator it(dir), end; it != end; ++it)
	{
		if(boost::filesystem::is_directory(*it))
		{ 
			SGE_LOG_WARNING(
				log(),
				sge::log::_1
					<< *it
					<< SGE_TEXT(" is a directory!"));
			continue;
		}

		if(boost::filesystem::basename(*it) == SGE_TEXT("probability"))
		{
			sge::string const dirname(
				boost::filesystem::basename(
					dir));

			sge::ifstream file(*it);
			if(!file.is_open() || !(file >> probability))
			{
				SGE_LOG_WARNING(
					log(),
					sge::log::_1
						<< SGE_TEXT("Failed reading probability file in \"")
						<< dirname
						<< SGE_TEXT("\"!"));
			}
			else
			{
				SGE_LOG_DEBUG(
					log(),
					sge::log::_1
						<< SGE_TEXT("Loaded sound probability ")
						<< probability
						<< SGE_TEXT(" in \"")
						<< dirname
						<< SGE_TEXT("\"!"));

				if(probability < static_cast<probability_type>(0) || probability > static_cast<probability_type>(1))
				{
					SGE_LOG_WARNING(
						log(),
						sge::log::_1
							<< SGE_TEXT("Invalid probability ")
							<< probability
							<< SGE_TEXT(" in \"")
							<< dirname
							<< SGE_TEXT("\"!"));
					probability = static_cast<probability_type>(1);
				}
			}
			
			continue;
		}
		container.push_back(ml.load(*it));
	}

	return sound_collection(
		container,
		probability);
}

sge::audio::sound_ptr const
sanguis::load::resource::sounds::make(
	sge::audio::file_ptr const snd) const
{
	sge::audio::sound_ptr const ss
		= player->create_nonstream_sound(
			snd);
	pool->add(ss);
	return ss;
}

sanguis::load::resource::sounds::sounds(
	sge::audio::multi_loader &ml,
	sge::audio::player_ptr const player,
	sge::audio::pool_ptr const pool)
:
	ml(ml),
	player(player),
	pool(pool)
{}
