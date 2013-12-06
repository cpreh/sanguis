#ifndef SANGUIS_SERVER_BUFFS_BURN_CREATE_HPP_INCLUDED
#define SANGUIS_SERVER_BUFFS_BURN_CREATE_HPP_INCLUDED

#include <sanguis/server/buffs/create_callback.hpp>
#include <sanguis/server/buffs/burn.hpp>
#include <sanguis/server/buffs/burn_interval.hpp>
#include <sanguis/server/buffs/unique_ptr.hpp>
#include <sanguis/server/damage/array_fwd.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/with_health.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/try_dynamic_cast.hpp>
#include <fcppt/config/external_begin.hpp>
#include <type_traits>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace buffs
{

template<
	typename Buff
>
sanguis::server::buffs::create_callback
burn_create(
	sanguis::diff_clock const &_diff_clock,
	sanguis::server::buffs::burn_interval const _interval,
	sanguis::server::damage::unit const _damage,
	sanguis::server::damage::array const &_damage_values
)
{
	static_assert(
		std::is_base_of<
			sanguis::server::buffs::burn,
			Buff
		>::value,
		"Buff must derive from buffs::slow"
	);

	return
		[
			&_diff_clock,
			_interval,
			_damage,
			_damage_values
		](
			sanguis::server::entities::base &_entity
		)
		{
			FCPPT_TRY_DYNAMIC_CAST(
				sanguis::server::entities::with_health *,
				with_health,
				&_entity
			)
				return
					sanguis::server::buffs::unique_ptr(
						fcppt::make_unique_ptr<
							Buff
						>(
							*with_health,
							_diff_clock,
							_interval,
							_damage,
							_damage_values

						)
					);

			return
				sanguis::server::buffs::unique_ptr();
		};
}

}
}
}

#endif
