#include "weapon.hpp"
#include "../entity_with_weapon.hpp"
#include "../../get_dim.hpp"
#include "../../message_converter.hpp"
#include "../../weapons/factory.hpp"
#include "../../../load/weapon_pickup_name.hpp"
#include "../../../messages/add_weapon_pickup.hpp"

sanguis::server::entities::pickups::weapon::weapon(
	environment const &env,
	messages::pos_type const &center,
	team::type const team_,
	weapon_type::type const weapon_type_)
:
	pickup(
		pickup_type::weapon,
		env,
		center,
		team_,
		default_dim(
			load::weapon_pickup_name(
				weapon_type_))),
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
	return message_convert(*this);
}

void sanguis::server::entities::pickups::weapon::do_pickup(
	entity_with_weapon &receiver)
{
	receiver.add_weapon(
		weapons::create(
			weapon_type_,
			get_environment()));
}
