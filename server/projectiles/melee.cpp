#include "melee.hpp"
#include <boost/assign/list_of.hpp>

sanguis::server::projectiles::melee::melee(
	environment const &env,
	armor_array const &armor,
	messages::pos_type const& pos,
	team::type const team_,
	messages::space_unit const damage)
: projectile(
	env,
	armor,
	pos,
	messages::mu(0),
	messages::mu(1), // some arbitrary health value
	team_,
	messages::mu(0),
	messages::mu(0),
	static_cast<time_type>(1)), // short lifetime
  damage(damage)
{}

sanguis::entity_type::type
sanguis::server::projectiles::melee::type() const
{
	return entity_type::indeterminate;
}

sanguis::messages::dim_type
sanguis::server::projectiles::melee::dim() const
{
	return messages::dim_type(1,1); // TODO: maybe allow cleaving attacks?
}

void sanguis::server::projectiles::melee::do_hit(
	entity &target)
{
	const damage_array damage_values =
		boost::assign::list_of
		(messages::mu(1))
		(messages::mu(0))
		(messages::mu(0))
		(messages::mu(0))
		(messages::mu(0));
			
	target.damage(
		damage,
		damage_values);
	die();
}
