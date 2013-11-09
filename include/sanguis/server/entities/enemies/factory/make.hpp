#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_FACTORY_MAKE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_FACTORY_MAKE_HPP_INCLUDED

#include <sanguis/server/exp.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/pickup_probability.hpp>
#include <sanguis/server/ai/create_function.hpp>
#include <sanguis/server/auras/container.hpp>
#include <sanguis/server/damage/armor.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <sanguis/server/entities/enemies/factory/parameters_fwd.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>


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
make(
	sanguis::server::entities::enemies::factory::parameters const &,
	sanguis::server::damage::armor const &,
	sanguis::server::health,
	sanguis::server::entities::movement_speed,
	sanguis::server::ai::create_function const &,
	sanguis::server::weapons::unique_ptr &&,
	sanguis::server::pickup_probability,
	sanguis::server::exp,
	sanguis::server::auras::container &&
);

}
}
}
}
}

#endif
