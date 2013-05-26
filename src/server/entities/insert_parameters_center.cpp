#include <sanguis/server/angle.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/entities/insert_parameters_center.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>


sanguis::server::entities::insert_parameters const
sanguis::server::entities::insert_parameters_center(
	sanguis::server::center const &_center
)
{
	return
		sanguis::server::entities::insert_parameters(
			_center,
			sanguis::server::angle(
				0.f
			)
		);
}
