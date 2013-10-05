#include <sanguis/server/speed.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/speed.hpp>
#include <sanguis/server/entities/ifaces/with_velocity.hpp>
#include <fcppt/try_dynamic_cast.hpp>


sanguis::server::speed const
sanguis::server::entities::speed(
	sanguis::server::entities::base const &_entity
)
{
	FCPPT_TRY_DYNAMIC_CAST(
		sanguis::server::entities::ifaces::with_velocity const *,
		with_velocity,
		&_entity
	)
		return
			with_velocity->speed();

	return
		sanguis::server::speed(
			sanguis::server::speed::value_type::null()
		);
}
