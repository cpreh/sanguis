#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_FACTORY_SKELETON_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_FACTORY_SKELETON_HPP_INCLUDED

#include <sanguis/server/entities/with_id_unique_ptr.hpp>
#include <sanguis/server/entities/enemies/factory/parameters_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{
namespace enemies
{
namespace factory
{

sanguis::server::entities::with_id_unique_ptr
skeleton(
	sanguis::server::entities::enemies::factory::parameters const &
);

}
}
}
}
}

#endif
