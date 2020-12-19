#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/enemies/attribute.hpp>
#include <sanguis/server/entities/enemies/parameters.hpp>
#include <sanguis/server/entities/enemies/modifiers/fast.hpp>
#include <sanguis/server/entities/enemies/modifiers/parameters_fwd.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cmath>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::enemies::attribute
sanguis::server::entities::enemies::modifiers::fast(
	fcppt::reference<
		sanguis::server::entities::enemies::parameters
	> const _parameters,
	sanguis::server::entities::enemies::modifiers::parameters const &
)
{
	_parameters->movement_speed(
		sanguis::server::entities::movement_speed(
			_parameters->movement_speed().get()
			*
			std::sqrt(
				_parameters->difficulty().get()
			)
		)
	);

	return
		sanguis::server::entities::enemies::attribute(
			FCPPT_TEXT("fast")
		);
}
