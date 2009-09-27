#include "friend.hpp"
#include "pickups/pickup.hpp"
#include "../weapons/weapon.hpp"
#include "../ai/base.hpp"
#include "../environment/load_context.hpp"
#include "../../load/friend_name.hpp"
#include "../../messages/add_friend.hpp"
#include "../../messages/create.hpp"
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/dim/basic_impl.hpp>
#include <boost/logic/tribool.hpp>

sanguis::server::entities::friend_::friend_(
	friend_type::type const ftype_,
	server::environment::load_context_ptr const load_context,
	damage::armor const &armor_,
	health_type const health_,
	server::movement_speed const movement_speed_,
	ai::create_function const &ai_,
	weapons::auto_ptr weapon_
)
:
	with_ai(
		ai_,
		weapon_
	),
	with_buffs(),
	with_dim(
		load_context->entity_dim(
			load::friend_name(
				ftype_
			)
		)
	),
	with_health(
		health_,
		armor_
	),
	movable(
		movement_speed_,
		static_cast<space_unit>(0)
	),
	ftype_(ftype_)
{}

void
sanguis::server::entities::friend_::on_update(
	time_type const time_
)
{
	with_ai::on_update(
		time_
	);

	with_buffs::on_update(
		time_
	);

	with_health::update(
		time_
	);
}

sanguis::entity_type::type
sanguis::server::entities::friend_::type() const
{
	return entity_type::friend_;
}

sanguis::server::team::type
sanguis::server::entities::friend_::team() const
{
	return server::team::players;
}

sanguis::messages::auto_ptr
sanguis::server::entities::friend_::add_message() const
{
	return messages::create(
		messages::add_friend(
			id(),
			pos(),
			angle(),
			abs_speed(),
			current_health(),
			max_health(),
			dim(),
			ftype_
		)
	);
}

boost::logic::tribool const
sanguis::server::entities::friend_::can_collide_with_entity(
	base const &e
) const
{
	return
		dynamic_cast<
			entities::pickups::pickup const *
		>(&e)
			? boost::logic::tribool(false)
			: boost::logic::indeterminate;
}
