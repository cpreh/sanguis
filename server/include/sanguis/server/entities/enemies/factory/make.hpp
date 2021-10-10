#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_FACTORY_MAKE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_FACTORY_MAKE_HPP_INCLUDED

#include <sanguis/server/exp_fwd.hpp>
#include <sanguis/server/health_fwd.hpp>
#include <sanguis/server/mass_fwd.hpp>
#include <sanguis/server/pickup_probability_fwd.hpp>
#include <sanguis/server/ai/create_function.hpp>
#include <sanguis/server/auras/container.hpp>
#include <sanguis/server/damage/armor_array_fwd.hpp>
#include <sanguis/server/entities/movement_speed_fwd.hpp>
#include <sanguis/server/entities/with_id_unique_ptr.hpp>
#include <sanguis/server/entities/enemies/factory/parameters_fwd.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>

namespace sanguis::server::entities::enemies::factory
{

sanguis::server::entities::with_id_unique_ptr make(
    sanguis::server::entities::enemies::factory::parameters const &,
    sanguis::server::damage::armor_array const &,
    sanguis::server::mass const &,
    sanguis::server::health,
    sanguis::server::entities::movement_speed,
    sanguis::server::ai::create_function &&,
    sanguis::server::weapons::unique_ptr &&,
    sanguis::server::pickup_probability,
    sanguis::server::exp,
    sanguis::server::auras::container &&);

}

#endif
