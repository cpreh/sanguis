#include "environment.hpp"
#include "../log.hpp"
#include "../../exception.hpp"
#include "map_get_or_create.hpp"
#include <sge/log/headers.hpp>
#include <sge/audio/player.hpp>
#include <sge/audio/pool.hpp>
#include <sge/random/uniform.hpp>
#include <boost/bind.hpp>
#include <boost/filesystem/operations.hpp>

sge::audio::sound_ptr const sanguis::load::resource::environment::load_sound(
	sge::path const &dir)
{
	/*
	SGE_LOG_DEBUG(
		log(),
		sge::log::_1 << SGE_TEXT(" loading sounds in ") 
		             << dir.string());
	*/

	sound_container &s = map_get_or_create(
		sounds, 
		dir, 
		boost::bind(&environment::do_load_sound,this,_1));

	if (s.size() > static_cast<sound_container::size_type>(0))
	{
		/*
		SGE_LOG_DEBUG(
			log(),
			sge::log::_1 << SGE_TEXT(" loaded ") << s.size() 
									 << SGE_TEXT(" sounds, choosing one randomly"));
										*/
	}
	
	static sge::random::uniform<sound_container::size_type> 
		rng(
			static_cast<sound_container::size_type>(0),
			static_cast<sound_container::size_type>(s.size()+1));

	if (s.size())
	{
		sge::audio::sound_ptr const ss = player->create_nonstream_sound(s[rng()]);
		sound_pool->add(ss);
		return ss;
	}

	return sge::audio::sound_ptr();
}

sanguis::load::resource::environment::sound_container const
	sanguis::load::resource::environment::do_load_sound(
		sge::path const &dir)
{
	// a missing directory is valid
	if (!boost::filesystem::exists(dir) || 
	    !boost::filesystem::is_directory(dir))
		return sound_container();

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

	return container;
}
