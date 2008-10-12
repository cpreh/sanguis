#include "environment.hpp"
#include "../log.hpp"
#include "../../exception.hpp"
#include "map_get_or_create.hpp"
#include <sge/log/headers.hpp>
#include <sge/audio/player.hpp>
#include <sge/audio/pool.hpp>
#include <sge/random/uniform.hpp>
#include <sge/random/last_exclusive_range.hpp>
#include <boost/bind.hpp>
#include <boost/filesystem/operations.hpp>

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

		container.push_back(ml.load(*it));
	}

	return sound_collection(
		container,
		sge::su(1)); // TODO: 100% for now
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
