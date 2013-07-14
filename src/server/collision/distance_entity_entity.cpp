#include <sanguis/server/center.hpp>
#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/collision/distance_entity_entity.hpp>
#include <sanguis/server/collision/distance_entity_pos.hpp>
#include <sanguis/server/entities/base.hpp>


sanguis::server::space_unit
sanguis::server::collision::distance_entity_entity(
	sanguis::server::entities::base const &_a,
	sanguis::server::entities::base const &_b
)
{
	return
		sanguis::server::collision::distance_entity_pos(
			_a,
			_b.center().get()
		);
}
