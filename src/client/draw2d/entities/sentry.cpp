#include <sanguis/client/draw2d/entities/sentry.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/sprite/index.hpp>
#include <sanguis/load/friend_name.hpp>
#include <fcppt/assign/make_container.hpp>

namespace
{

sanguis::client::draw2d::sprite::index const
	top(1),
	bottom(0);

}

sanguis::client::draw2d::entities::sentry::sentry(
	model::parameters const &_param
)
:
	model::object(
		_param,
		load::friend_name(
			friend_type::sentry
		),
		fcppt::assign::make_container<
			entities::order_vector
		>(
			z_ordering::player_lower
		)(
			z_ordering::player_upper
		),
		model::needs_healthbar::yes,
		model::decay_option::delayed
	)
{
}

sanguis::client::draw2d::entities::sentry::~sentry()
{
}

void
sanguis::client::draw2d::entities::sentry::orientation(
	sprite::rotation const _rotation
)
{
	model::object::orientation(
		_rotation,
		top // TODO
	);
}
