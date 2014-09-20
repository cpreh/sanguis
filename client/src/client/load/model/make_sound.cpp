#include <sanguis/client/load/log.hpp>
#include <sanguis/client/load/model/make_sound.hpp>
#include <sanguis/client/load/resource/optional_sound.hpp>
#include <sanguis/client/load/resource/sounds.hpp>
#include <sanguis/model/animation_sound.hpp>
#include <sanguis/model/optional_animation_sound.hpp>
#include <fcppt/optional_bind.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/error.hpp>


sanguis::client::load::resource::optional_sound
sanguis::client::load::model::make_sound(
	sanguis::model::optional_animation_sound const &_opt_sound,
	sanguis::client::load::resource::sounds const &_sounds
)
{
	return
		fcppt::optional_bind(
			_opt_sound,
			[
				&_sounds
			](
				sanguis::model::animation_sound const &_sound
			)
			{
				sanguis::client::load::resource::optional_sound const result{
					_sounds.load(
						_sound.get()
					)
				};

				if(
					!result
				)
					FCPPT_LOG_ERROR(
						sanguis::client::load::log(),
						fcppt::log::_
							<< FCPPT_TEXT("Unable to load sound ")
							<< _sound
					);

				return
					result;
			}
		);
}
