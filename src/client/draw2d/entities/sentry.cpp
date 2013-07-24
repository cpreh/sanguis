#include <sanguis/friend_type.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/entities/sentry.hpp>
#include <sanguis/client/draw2d/entities/model/decay_option.hpp>
#include <sanguis/client/draw2d/entities/model/needs_healthbar.hpp>
#include <sanguis/client/draw2d/entities/model/object.hpp>
#include <sanguis/client/draw2d/entities/model/parameters_fwd.hpp>
#include <sanguis/client/draw2d/sprite/index.hpp>
#include <sanguis/client/draw2d/sprite/rotation.hpp>
#include <sanguis/load/friend_name.hpp>


namespace
{

sanguis::client::draw2d::sprite::index const
	top(1),
	bottom(0);

}

sanguis::client::draw2d::entities::sentry::sentry(
	sanguis::client::draw2d::entities::model::parameters const &_param
)
:
	sanguis::client::draw2d::entities::model::object(
		_param,
		sanguis::load::friend_name(
			sanguis::friend_type::sentry
		),
		sanguis::client::draw2d::entities::order_vector{
			sanguis::client::draw2d::z_ordering::player_lower,
			sanguis::client::draw2d::z_ordering::player_upper
		},
		sanguis::client::draw2d::entities::model::needs_healthbar::yes,
		sanguis::client::draw2d::entities::model::decay_option::delayed
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
