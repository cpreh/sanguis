#include <sanguis/server/center.hpp>
#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/vector.hpp>
#include <sanguis/server/collision/distance_entity_pos.hpp>
#include <sanguis/server/collision/distance_pos_pos.hpp>
#include <sanguis/server/entities/base.hpp>

sanguis::server::space_unit sanguis::server::collision::distance_entity_pos(
    sanguis::server::entities::base const &_a, sanguis::server::vector const &_b)
{
  return sanguis::server::collision::distance_pos_pos(_a.center().get(), _b);
}
