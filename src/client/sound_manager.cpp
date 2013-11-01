#include <sge/audio/sound/base.hpp>
#include <sge/audio/sound/base_unique_ptr.hpp>
#include <sge/audio/sound/do_pause.hpp>
#include <sge/audio/sound/pause_or_resume.hpp>
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
	if(
		!_sound
	)
		return;

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
sanguis::client::sound_manager::pause(
	bool const _value
)
{
	for(
		auto &sound
		:
		sounds_
	)
		sge::audio::sound::pause_or_resume(
			*sound,
			sge::audio::sound::do_pause(
				_value
			)
		);
}

void
sanguis::client::sound_manager::update()
{
	// TODO: sequence_iteration
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
