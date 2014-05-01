#include <sanguis/creator/destructible.hpp>
#include <sanguis/server/angle.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/world/grid_pos_to_center.hpp>
#include <sanguis/server/world/destructible_parameters.hpp>


sanguis::server::entities::insert_parameters const
sanguis::server::world::destructible_parameters(
	sanguis::creator::destructible const &_destructible
)
{
	return
		sanguis::server::entities::insert_parameters(
			sanguis::server::world::grid_pos_to_center(
				_destructible.pos().get()
			),
			sanguis::server::angle(
				0.f // TODO
			)
		);
}
