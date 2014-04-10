#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_FACTORY_ZOMBIE01_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_FACTORY_ZOMBIE01_HPP_INCLUDED

#include <sanguis/server/entities/unique_ptr.hpp>
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

sanguis::server::entities::unique_ptr
zombie01(
	sanguis::server::entities::enemies::factory::parameters const &
);

}
}
}
}
}

#endif
