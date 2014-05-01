#ifndef SANGUIS_SERVER_AURAS_SLOW_CREATE_HPP_INCLUDED
#define SANGUIS_SERVER_AURAS_SLOW_CREATE_HPP_INCLUDED

#include <sanguis/aura_type.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/auras/buff.hpp>
#include <sanguis/server/auras/create_callback.hpp>
#include <sanguis/server/auras/influence.hpp>
#include <sanguis/server/buffs/slow_create.hpp>
#include <sanguis/server/buffs/slow_factor.hpp>


namespace sanguis
{
namespace server
{
namespace auras
{

template<
	typename Buff
>
sanguis::server::auras::create_callback
slow_create(
	sanguis::server::radius const _radius,
	sanguis::server::team const _team,
	sanguis::server::buffs::slow_factor const _factor
)
{
	return
		sanguis::server::auras::create_callback(
			[
				_radius,
				_team,
				_factor
			](
				sanguis::diff_clock const &
			)
			{
				return
					fcppt::make_unique_ptr<
						sanguis::server::auras::buff
					>(
						_radius,
						_team,
						sanguis::aura_type::slow,
						sanguis::server::auras::influence::debuff,
						sanguis::server::buffs::slow_create<
							Buff
						>(
							_factor
						)
					);
			}
		);
}

}
}
}

#endif
