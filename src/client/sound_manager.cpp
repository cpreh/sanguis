#include <sge/audio/sound/base.hpp>
#include <sge/audio/sound/base_unique_ptr.hpp>
#include <sge/audio/sound/play_status.hpp>
#include <sge/audio/sound/repeat.hpp>
#include <sanguis/client/sound_manager.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::client::sound_manager::sound_manager()
:
	sounds_()
{
}

sanguis::client::sound_manager::~sound_manager()
{
}

void
sanguis::client::sound_manager::add(
	sge::audio::sound::base_unique_ptr &&_sound
)
{
	_sound->play(
		sge::audio::sound::repeat::once
	);

	sounds_.push_back(
		std::move(
			_sound
		)
	);
}

void
sanguis::client::sound_manager::update()
{
	for(
		sound_list::iterator it(
			sounds_.begin()
		);
		it != sounds_.end();
	)
	{
		sge::audio::sound::base &sound(
			**it
		);

		sound.update();

		if(
			sound.status()
			!=
			sge::audio::sound::play_status::playing
		)
			it =
				sounds_.erase(
					it
				);
		else
			++it;
	}
}
