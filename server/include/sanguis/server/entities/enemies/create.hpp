#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_CREATE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_CREATE_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/creator/enemy_kind_fwd.hpp>
#include <sanguis/creator/enemy_type_fwd.hpp>
#include <sanguis/server/entities/spawn_owner_fwd.hpp>
#include <sanguis/server/entities/with_id_unique_ptr.hpp>
#include <sanguis/server/entities/enemies/special_chance.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/world/difficulty.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{
namespace enemies
{

sanguis::server::entities::with_id_unique_ptr
create(
	sanguis::random_generator &,
	sanguis::creator::enemy_type,
	sanguis::creator::enemy_kind,
	sanguis::server::world::difficulty,
	sanguis::server::environment::load_context &,
	sanguis::server::entities::spawn_owner const &,
	sanguis::server::entities::enemies::special_chance
);

}
}
}
}

#endif
