#include <sanguis/duration.hpp>
#include <sanguis/exception.hpp>
#include <sanguis/client/load/model/make_delay.hpp>
#include <sanguis/model/animation.hpp>
#include <sanguis/model/optional_animation_delay.hpp>
#include <fcppt/optional_to_exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <fcppt/config/external_end.hpp>


sanguis::duration const
sanguis::client::load::model::make_delay(
	sanguis::model::animation const &_animation,
	sanguis::model::optional_animation_delay const &_header_delay
)
{
	return
		std::chrono::duration_cast<
			sanguis::duration
		>(
			fcppt::optional_to_exception(
				_animation.animation_delay().has_value()
				?
					_animation.animation_delay()
				:
					_header_delay
				,
				[]{
					return
						sanguis::exception(
							FCPPT_TEXT("delay not in header but not in specified leaf TODO either!")
						);
				}
			).get()
		);
}
