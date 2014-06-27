#ifndef SANGUIS_SERVER_PERKS_CONSTANT_DAMAGE_CHANGE_HPP_INCLUDED
#define SANGUIS_SERVER_PERKS_CONSTANT_DAMAGE_CHANGE_HPP_INCLUDED

#include <sanguis/server/damage/type_fwd.hpp>
#include <sanguis/server/entities/with_perks_fwd.hpp>
#include <sanguis/server/perks/change_factor.hpp>
#include <sanguis/server/perks/level_diff.hpp>


namespace sanguis
{
namespace server
{
namespace perks
{

void
constant_damage_change(
	sanguis::server::entities::with_perks &,
	sanguis::server::damage::type,
	sanguis::server::perks::level_diff,
	sanguis::server::perks::change_factor
);

}
}
}

#endif
