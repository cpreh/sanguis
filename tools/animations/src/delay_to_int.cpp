#include <sanguis/model/animation_delay.hpp>
#include <sanguis/tools/animations/delay_to_int.hpp>
#include <fcppt/cast/size.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <fcppt/config/external_end.hpp>

int
sanguis::tools::animations::delay_to_int(
	sanguis::model::animation_delay const &_delay
)
{
	return
		fcppt::cast::size<
			int
		>(
			std::chrono::duration_cast<
				std::chrono::milliseconds
			>(
				_delay.get()
			).count()
		);
}
