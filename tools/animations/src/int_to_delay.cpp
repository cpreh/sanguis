#include <sanguis/model/animation_delay.hpp>
#include <sanguis/model/optional_animation_delay.hpp>
#include <sanguis/tools/animations/int_to_delay.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <fcppt/config/external_end.hpp>


sanguis::model::optional_animation_delay const
sanguis::tools::animations::int_to_delay(
	int const _value
)
{
	return
		_value
		!=
		0
		?
			sanguis::model::optional_animation_delay(
				sanguis::model::animation_delay(
					std::chrono::milliseconds(
						_value
					)
				)
			)
		:
			sanguis::model::optional_animation_delay()
		;
}
