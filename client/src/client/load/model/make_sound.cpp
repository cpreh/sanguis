#include <sanguis/client/load/log.hpp>
#include <sanguis/client/load/model/make_sound.hpp>
#include <sanguis/client/load/model/optional_sound.hpp>
#include <sanguis/client/load/resource/sounds_fwd.hpp>
#include <sanguis/model/optional_animation_sound.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/error.hpp>


sanguis::client::load::model::optional_sound
sanguis::client::load::model::make_sound(
	sanguis::model::optional_animation_sound const &_sound,
	sanguis::client::load::resource::sounds const &_sounds
)
{
	if(
		!_sound
	)
		return
			sanguis::client::load::model::optional_sound();

	sanguis::client::load::model::sound const result(
		_sound->get(),
		_sounds
	);

	if(
		!result.buffer()
	)
	{
		FCPPT_LOG_ERROR(
			sanguis::client::load::log(),
			fcppt::log::_
				<< FCPPT_TEXT("Unable to load sound ")
				<< _sound->get()
		);

		return
			sanguis::client::load::model::optional_sound();
	}

	return
		sanguis::client::load::model::optional_sound(
			result
		);
}
