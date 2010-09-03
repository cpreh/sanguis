#include "friend.hpp"
#include "pickups/pickup.hpp"
#include "property/initial.hpp"
#include "../weapons/weapon.hpp"
#include "../ai/base.hpp"
#include "../environment/load_context.hpp"
#include "../../load/friend_name.hpp"
#include "../../messages/add_friend.hpp"
#include "../../messages/create.hpp"
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <boost/logic/tribool.hpp>

sanguis::server::entities::friend_::friend_(
	friend_type::type const _ftype,
	server::environment::load_context_ptr const _load_context,
	damage::armor const &_armor,
	health_type const _health,
	entities::movement_speed const _movement_speed,
	ai::create_function const &_ai,
	weapons::unique_ptr _weapon
)
:
	with_ai(
		_ai,
		move(
			_weapon
		)
	),
	with_buffs(),
	with_dim(
		_load_context->entity_dim(
			load::friend_name(
				_ftype
			)
		)
	),
	with_health(
		_health,
		_armor
	),
	movable(
		property::initial(
			_movement_speed,
			0
		),
		static_cast<space_unit>(0)
	),
	ftype_(_ftype)
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

	with_health::on_update(
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
sanguis::server::entities::friend_::add_message(
	server::player_id const
) const
{
	return messages::create(
		messages::add_friend(
			id(),
			pos(),
			angle(),
			dim(),
			abs_speed(),
			current_health(),
			max_health(),
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
