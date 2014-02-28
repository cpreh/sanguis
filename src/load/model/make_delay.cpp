#include <sanguis/duration.hpp>
#include <sanguis/exception.hpp>
#include <sanguis/load/model/make_delay.hpp>
#include <sanguis/model/animation.hpp>
#include <sanguis/model/optional_animation_delay.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <fcppt/config/external_end.hpp>


sanguis::duration const
sanguis::load::model::make_delay(
	sanguis::model::animation const &_animation,
	sanguis::model::optional_animation_delay const &_header_delay
)
{
	sanguis::model::optional_animation_delay const delay(
		_animation.animation_delay()
		?
			_animation.animation_delay()
		:
			_header_delay
	);

	if(
		!delay
	)
		throw
			sanguis::exception(
				FCPPT_TEXT("delay not in header but not in specified leaf TODO either!")
			);

	return
		std::chrono::duration_cast<
			sanguis::duration
		>(
			delay->get()
		);
}
