#ifndef SANGUIS_SERVER_BUFFS_SLOW_CREATE_HPP_INCLUDED
#define SANGUIS_SERVER_BUFFS_SLOW_CREATE_HPP_INCLUDED

#include <sanguis/server/buffs/create_callback.hpp>
#include <sanguis/server/buffs/slow.hpp>
#include <sanguis/server/buffs/slow_factor.hpp>
#include <sanguis/server/buffs/unique_ptr.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/with_velocity.hpp>
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
slow_create(
	sanguis::server::buffs::slow_factor const _factor
)
{
	static_assert(
		std::is_base_of<
			sanguis::server::buffs::slow,
			Buff
		>::value,
		"Buff must derive from buffs::slow"
	);

	return
		[
			_factor
		](
			sanguis::server::entities::base &_entity
		)
		{
			FCPPT_TRY_DYNAMIC_CAST(
				sanguis::server::entities::with_velocity *,
				with_velocity,
				&_entity
			)
				return
					sanguis::server::buffs::unique_ptr(
						fcppt::make_unique_ptr<
							Buff
						>(
							*with_velocity,
							_factor

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
