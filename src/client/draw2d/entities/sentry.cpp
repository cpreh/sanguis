#include <sanguis/aura_type_vector.hpp>
#include <sanguis/buff_type_vector.hpp>
#include <sanguis/friend_type.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/entities/friend.hpp>
#include <sanguis/client/draw2d/entities/order_vector.hpp>
#include <sanguis/client/draw2d/entities/sentry.hpp>
#include <sanguis/client/draw2d/entities/model/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/model/object.hpp>
#include <sanguis/client/draw2d/sprite/index.hpp>
#include <sanguis/client/draw2d/sprite/rotation.hpp>
#include <sanguis/load/auras/context_fwd.hpp>


namespace
{

sanguis::client::draw2d::sprite::index const
	top(1),
	bottom(0);

}

sanguis::client::draw2d::entities::sentry::sentry(
	sanguis::client::draw2d::entities::model::load_parameters const &_load_parameters,
	sanguis::load::auras::context &_aura_resources,
	sanguis::aura_type_vector const &_auras,
	sanguis::buff_type_vector const &_buffs
)
:
	sanguis::client::draw2d::entities::friend_(
		_load_parameters,
		_aura_resources,
		sanguis::friend_type::sentry,
		_auras,
		_buffs,
		sanguis::client::draw2d::entities::order_vector{
			sanguis::client::draw2d::z_ordering::player_lower,
			sanguis::client::draw2d::z_ordering::player_upper
		}
	)
{
}

sanguis::client::draw2d::entities::sentry::~sentry()
{
}

void
sanguis::client::draw2d::entities::sentry::orientation(
	sanguis::client::draw2d::sprite::rotation const _rotation
)
{
	sanguis::client::draw2d::entities::model::object::orientation(
		_rotation,
		top // TODO
	);
}
