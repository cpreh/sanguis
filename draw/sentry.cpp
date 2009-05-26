#include "sentry.hpp"
#include "z_ordering.hpp"
#include "sprite_part_index.hpp"
#include "object.hpp"
#include "../load/friend_name.hpp"

namespace
{

sanguis::draw::sprite_part_index const
	top(1),
	bottom(0);

}

sanguis::draw::sentry::sentry(
	draw::environment const &env,
	entity_id const id)
:
	model(
		env,
		id,
		load::friend_name(
			friend_type::sentry
		),
		z_ordering::model_generic,
		true,
		draw::remove_action::render_dead
	)
{
	at(bottom).order(z_ordering::player_lower);
	at(top).order(z_ordering::player_upper); // FIXME
}

void
sanguis::draw::sentry::orientation(
	sge::sprite::rotation_type const rot)
{
	model::orientation(rot, 1);
}
