#include "sounds.hpp"
#include "map_get_or_create.hpp"
#include "../sound_collection.hpp"
#include "../log.hpp"
#include "../../exception.hpp"
#include <sge/filesystem/exists.hpp>
#include <sge/filesystem/is_directory.hpp>
#include <sge/filesystem/directory_iterator.hpp>
#include <sge/filesystem/stem.hpp>
#include <sge/log/headers.hpp>
#include <sge/audio/player.hpp>
#include <sge/audio/pool.hpp>
#include <sge/audio/multi_loader.hpp>
#include <sge/fstream.hpp>
#include <sge/text.hpp>
#include <boost/bind.hpp>
#include <istream>
#include <ostream>

sanguis::load::sound_collection const &
sanguis::load::resource::sounds::load(
	sge::filesystem::path const &dir) const
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
	sge::filesystem::path const &dir) const
{
	// a missing directory is valid
	if (!sge::filesystem::exists(dir) || 
	    !sge::filesystem::is_directory(dir))
		return sound_collection(
			sound_container(),
			static_cast<probability_type>(0));

	sound_container container;
	probability_type probability(
		static_cast<probability_type>(1));

	for(sge::filesystem::directory_iterator it(dir), end; it != end; ++it)
	{
		if(sge::filesystem::is_directory(*it))
		{ 
			SGE_LOG_WARNING(
				log(),
				sge::log::_1
					<< it->path().string()
					<< SGE_TEXT(" is a directory!"));
			continue;
		}

		if(sge::filesystem::stem(*it) == SGE_TEXT("probability"))
		{
			sge::string const dirname(
				sge::filesystem::stem(
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
	sge::audio::file_ptr const snd,
	sound_type::type const t) const
{
	sge::audio::sound_ptr ss;
	switch (t)
	{
		case sound_type::stream:
			ss = player->create_stream_sound(
				snd);
		break;
		case sound_type::nonstream:
			ss = player->create_nonstream_sound(
				snd);
		break;
	}
	pool.add(
		ss,
		sge::audio::stop_mode::continue_playing);
	return ss;
}

sanguis::load::resource::sounds::sounds(
	sge::audio::multi_loader &ml,
	sge::audio::player_ptr const player,
	sge::audio::pool &pool)
:
	ml(ml),
	player(player),
	pool(pool)
{}
