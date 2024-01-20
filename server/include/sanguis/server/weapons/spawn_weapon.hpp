#ifndef SANGUIS_SERVER_WEAPONS_SPAWN_WEAPON_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_SPAWN_WEAPON_HPP_INCLUDED

#include <sanguis/server/weapons/create_function.hpp>
#include <fcppt/declare_strong_typedef.hpp>
#include <fcppt/strong_typedef_impl.hpp> // IWYU pragma: keep

namespace sanguis::server::weapons
{

FCPPT_DECLARE_STRONG_TYPEDEF(sanguis::server::weapons::create_function, spawn_weapon);

}

#endif
