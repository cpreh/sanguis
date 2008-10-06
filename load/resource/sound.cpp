#include "environment.hpp"
#include "../log.hpp"
#include "../../exception.hpp"
#include <sge/audio/player.hpp>
#include <sge/log/headers.hpp>
#include <boost/filesystem/operations.hpp>

sanguis::load::resource::environment::sound_container const
	sanguis::load::resource::environment::do_load_sound(
		sge::path const &dir)
{
	if (!boost::filesystem::exists(dir) || 
	    !boost::filesystem::is_directory(dir))
		throw exception(
			SGE_TEXT("directory for sounds \"")+dir.string()+SGE_TEXT("\" doesn't exist"));

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

		container.push_back(player->create_nonstream_sound(ml.load(dir)));
	}

	return container;
}
