#include <sanguis/server/entities/insert_parameters_center.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/angle.hpp>

sanguis::server::entities::insert_parameters const
sanguis::server::entities::insert_parameters_center(
	server::center const &_center
)
{
	return
		entities::insert_parameters(
			_center,
			server::angle(
				0.f
			)
		);
}
