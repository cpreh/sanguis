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
#include <sanguis/server/entities/base_ref.hpp>
#include <sanguis/server/entities/with_health.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/optional/map.hpp>
#include <fcppt/preprocessor/disable_gcc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
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
		std::is_base_of_v<
			sanguis::server::buffs::burn,
			Buff
		>,
		"Buff must derive from buffs::slow"
	);

	return
		sanguis::server::buffs::create_callback{
			[
				_interval,
				_damage,
				_damage_values
			](
				sanguis::server::entities::base_ref const _entity
			)
			{
FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_GCC_WARNING(-Wattributes)
				return
					fcppt::optional::map(
						fcppt::cast::dynamic<
							sanguis::server::entities::with_health
						>(
							_entity.get()
						),
						[
							_interval,
							_damage,
							_damage_values
						](
							fcppt::reference<
								sanguis::server::entities::with_health
							> const _with_health
						)
						{
							return
								fcppt::unique_ptr_to_base<
									sanguis::server::buffs::buff
								>(
									fcppt::make_unique_ptr<
										Buff
									>(
										_with_health,
										_interval,
										_damage,
										sanguis::server::damage::unmodified(
											_damage_values
										)
									)
								);
						}
					);
FCPPT_PP_POP_WARNING
			}
		};
}

}
}
}

#endif
