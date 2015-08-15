#ifndef SANGUIS_SERVER_BUFFS_BURN_CREATE_HPP_INCLUDED
#define SANGUIS_SERVER_BUFFS_BURN_CREATE_HPP_INCLUDED

#include <sanguis/server/buffs/buff.hpp>
#include <sanguis/server/buffs/burn.hpp>
#include <sanguis/server/buffs/burn_interval.hpp>
#include <sanguis/server/buffs/create_callback.hpp>
#include <sanguis/server/buffs/unique_ptr.hpp>
#include <sanguis/server/damage/array_fwd.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/damage/unmodified.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/with_health.hpp>
#include <fcppt/make_unique_ptr_fcppt.hpp>
#include <fcppt/optional_bind_construct.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/cast/try_dynamic.hpp>
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
		sanguis::server::buffs::create_callback{
			[
				_interval,
				_damage,
				_damage_values
			](
				sanguis::server::entities::base &_entity
			)
			{
				return
					fcppt::optional_bind_construct(
						fcppt::cast::try_dynamic<
							sanguis::server::entities::with_health &
						>(
							_entity
						),
						[
							_interval,
							_damage,
							_damage_values
						](
							sanguis::server::entities::with_health &_with_health
						)
						{
							return
								fcppt::unique_ptr_to_base<
									sanguis::server::buffs::buff
								>(
									fcppt::make_unique_ptr_fcppt<
										Buff
									>(
										_with_health,
										_interval,
										_damage,
										// TODO: Auras must know their owner to fix this
										sanguis::server::damage::unmodified(
											_damage_values
										)
									)
								);
						}
					);
			}
		};
}

}
}
}

#endif
