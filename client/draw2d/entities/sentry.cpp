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
	model::parameters const &param_
)
:
	model::object(
		param_,
		load::friend_name(
			friend_type::sentry
		),
		z_ordering::model_generic,
		model::needs_healthbar::yes,
		model::decay_option::delayed
	)
{
	at(bottom).order(z_ordering::player_lower);
	at(top).order(z_ordering::player_upper); // FIXME
}

void
sanguis::client::draw2d::entities::sentry::orientation(
	sprite::rotation_type const rot
)
{
	model::object::orientation(rot, 1);
}
