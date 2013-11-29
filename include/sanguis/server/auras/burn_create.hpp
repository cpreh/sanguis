#ifndef SANGUIS_SERVER_AURAS_BURN_CREATE_HPP_INCLUDED
#define SANGUIS_SERVER_AURAS_BURN_CREATE_HPP_INCLUDED

#include <sanguis/aura_type.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/auras/buff.hpp>
#include <sanguis/server/auras/influence.hpp>
#include <sanguis/server/auras/unique_ptr.hpp>
#include <sanguis/server/buffs/burn_create.hpp>
#include <sanguis/server/buffs/burn_interval.hpp>
#include <sanguis/server/damage/fire.hpp>
#include <sanguis/server/damage/list.hpp>
#include <sanguis/server/damage/unit.hpp>


namespace sanguis
{
namespace server
{
namespace auras
{

template<
	typename Buff
>
sanguis::server::auras::unique_ptr
burn_create(
	sanguis::diff_clock const &_diff_clock,
	sanguis::server::radius const _radius,
	sanguis::server::team const _team,
	sanguis::server::buffs::burn_interval const _interval,
	sanguis::server::damage::unit const _damage
)
{
	return
		fcppt::make_unique_ptr<
			sanguis::server::auras::buff
		>(
			_radius,
			_team,
			sanguis::aura_type::burn,
			sanguis::server::auras::influence::debuff,
			sanguis::server::buffs::burn_create<
				Buff
			>(
				_diff_clock,
				_interval,
				_damage,
				sanguis::server::damage::list(
					sanguis::server::damage::fire =
						sanguis::server::damage::unit(
							1.f
						)
				)
			)
		);
}

}
}
}

#endif
