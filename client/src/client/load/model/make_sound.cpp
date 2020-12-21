#include <sanguis/client/load/model/make_sound.hpp>
#include <sanguis/client/load/resource/optional_sound.hpp>
#include <sanguis/client/load/resource/sounds.hpp>
#include <sanguis/client/load/resource/sounds_cref.hpp>
#include <sanguis/model/animation_sound.hpp>
#include <sanguis/model/optional_animation_sound.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/log/out.hpp>
#include <fcppt/optional/bind.hpp>


sanguis::client::load::resource::optional_sound
sanguis::client::load::model::make_sound(
	fcppt::log::object &_log,
	sanguis::model::optional_animation_sound const &_opt_sound,
	sanguis::client::load::resource::sounds_cref const _sounds
)
{
	return
		fcppt::optional::bind(
			_opt_sound,
			[
				&_log,
				&_sounds
			](
				sanguis::model::animation_sound const &_sound
			)
			{
				sanguis::client::load::resource::optional_sound const result{
					_sounds->load(
						_sound.get()
					)
				};

				if(
					!result.has_value()
				)
				{
					FCPPT_LOG_ERROR(
						_log,
						fcppt::log::out
							<< FCPPT_TEXT("Unable to load sound ")
							<< _sound
					)
				}

				return
					result;
			}
		);
}
