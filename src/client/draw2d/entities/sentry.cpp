#include "sentry.hpp"
#include "../z_ordering.hpp"
#include "../sprite/index.hpp"
#include "../../../load/friend_name.hpp"
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/intrusive/system_impl.hpp>

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
		z_ordering::model_generic,
		model::needs_healthbar::yes,
		model::decay_option::delayed
	)
{
	this->at(
		bottom
	).order(
		z_ordering::player_lower
	);

	this->at(
		top
	).order(
		z_ordering::player_upper
	); // FIXME
}

sanguis::client::draw2d::entities::sentry::~sentry()
{
}

void
sanguis::client::draw2d::entities::sentry::orientation(
	sprite::rotation_type const _rotation
)
{
	model::object::orientation(
		_rotation,
		top.get() // TODO
	);
}
