#include <sanguis/creator/spawn.hpp>
#include <sanguis/server/angle.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/world/grid_pos_to_center.hpp>
#include <sanguis/server/world/spawn_parameters.hpp>


sanguis::server::entities::insert_parameters
sanguis::server::world::spawn_parameters(
	sanguis::creator::spawn const &_spawn
)
{
	return
		sanguis::server::entities::insert_parameters(
			sanguis::server::world::grid_pos_to_center(
				_spawn.pos().get()
			),
			sanguis::server::angle(
				0.f // TODO
			)
		);
}
