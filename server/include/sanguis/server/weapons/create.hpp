#ifndef SANGUIS_SERVER_WEAPONS_CREATE_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_CREATE_HPP_INCLUDED

#include <sanguis/weapon_type_fwd.hpp>
#include <sanguis/server/entities/enemies/difficulty.hpp>
#include <sanguis/server/weapons/common_parameters_fwd.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>

namespace sanguis::server::weapons
{

sanguis::server::weapons::unique_ptr create(
    sanguis::server::weapons::common_parameters const &,
    sanguis::weapon_type,
    sanguis::server::entities::enemies::difficulty);

}

#endif
