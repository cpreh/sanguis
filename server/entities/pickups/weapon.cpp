#include "weapon.hpp"
#include "../entity_with_weapon.hpp"
#include "../../weapons/weapon.hpp"
#include "../../weapons/factory.hpp"
#include "../../environment/load_context.hpp"
#include "../../../load/weapon_pickup_name.hpp"
#include "../../../messages/create.hpp"
#include "../../../messages/add_weapon_pickup.hpp"
#include <sge/optional_impl.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/dim/basic_impl.hpp>

sanguis::server::entities::pickups::weapon::weapon(
	server::environment::load_context_ptr const load_context,
	team::type const team_,
	weapon_type::type const weapon_type_
)
:
	pickup(
		pickup_type::weapon,
		load_context,
		team_,
		load_context->entity_dim(
			load::weapon_pickup_name(
				weapon_type_
			)
		)
	),
	weapon_type_(weapon_type_)
{}

sanguis::weapon_type::type
sanguis::server::entities::pickups::weapon::wtype() const
{
	return weapon_type_;
}

sanguis::messages::auto_ptr
sanguis::server::entities::pickups::weapon::add_message() const
{
	return messages::create(
		messages::add_weapon_pickup(
			id(),
			pos(),
			angle(),
			abs_speed(),
			health(),
			max_health(),
			dim(),
			wtype()
		)
	);
}

void
sanguis::server::entities::pickups::weapon::do_pickup(
	entity_with_weapon &receiver)
{
	receiver.add_weapon(
		weapons::create(
			weapon_type_
		)
	);
}
