#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/enemies/attribute.hpp>
#include <sanguis/server/entities/enemies/parameters.hpp>
#include <sanguis/server/entities/enemies/modifiers/fast.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cmath>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::enemies::attribute
sanguis::server::entities::enemies::modifiers::fast(
	sanguis::server::entities::enemies::parameters &_parameters
)
{
	_parameters.movement_speed(
		sanguis::server::entities::movement_speed(
			_parameters.movement_speed().get()
			*
			std::sqrt(
				_parameters.difficulty().get()
			)
		)
	);

	return
		sanguis::server::entities::enemies::attribute(
			FCPPT_TEXT("fast")
		);
}
