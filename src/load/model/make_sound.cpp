#include <sanguis/load/log.hpp>
#include <sanguis/load/model/make_sound.hpp>
#include <sanguis/load/model/optional_sound.hpp>
#include <sanguis/load/resource/sounds_fwd.hpp>
#include <sanguis/model/optional_animation_sound.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/error.hpp>


sanguis::load::model::optional_sound
sanguis::load::model::make_sound(
	sanguis::model::optional_animation_sound const &_sound,
	sanguis::load::resource::sounds const &_sounds
)
{
	if(
		!_sound
	)
		return
			sanguis::load::model::optional_sound();

	sanguis::load::model::sound const result(
		_sound->get(),
		_sounds
	);

	if(
		!result.buffer()
	)
	{
		FCPPT_LOG_ERROR(
			sanguis::load::log(),
			fcppt::log::_
				<< FCPPT_TEXT("Unable to load sound ")
				<< _sound->get()
		);

		return
			sanguis::load::model::optional_sound();
	}

	return
		sanguis::load::model::optional_sound(
			result
		);
}
