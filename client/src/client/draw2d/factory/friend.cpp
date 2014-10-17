#include <sanguis/aura_type_vector.hpp>
#include <sanguis/buff_type_vector.hpp>
#include <sanguis/friend_type.hpp>
#include <sanguis/client/health_pair.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/entities/friend.hpp>
#include <sanguis/client/draw2d/entities/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/order_vector.hpp>
#include <sanguis/client/draw2d/entities/sentry.hpp>
#include <sanguis/client/draw2d/factory/friend.hpp>
#include <sanguis/client/load/auras/context_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/assert/unreachable.hpp>


sanguis::client::draw2d::entities::unique_ptr
sanguis::client::draw2d::factory::friend_(
	sanguis::client::draw2d::entities::load_parameters const &_parameters,
	sanguis::client::load::auras::context &_aura_load_context,
	sanguis::friend_type const _friend_type,
	sanguis::aura_type_vector const &_auras,
	sanguis::buff_type_vector const &_buffs,
	sanguis::client::health_pair const _health_pair
)
{
	switch(
		_friend_type
	)
	{
	case sanguis::friend_type::spider:
		return
			sanguis::client::draw2d::entities::unique_ptr(
				fcppt::make_unique_ptr<
					sanguis::client::draw2d::entities::friend_
				>(
					_parameters,
					_aura_load_context,
					_friend_type,
					_auras,
					_buffs,
					sanguis::client::draw2d::entities::order_vector{
						sanguis::client::draw2d::z_ordering::model_generic
					},
					_health_pair
				)
			);
	case sanguis::friend_type::sentry:
		return
			sanguis::client::draw2d::entities::unique_ptr(
				fcppt::make_unique_ptr<
					sanguis::client::draw2d::entities::sentry
				>(
					_parameters,
					_aura_load_context,
					_auras,
					_buffs,
					_health_pair
				)
			);
	}

	FCPPT_ASSERT_UNREACHABLE;
}
