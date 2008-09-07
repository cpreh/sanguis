#include "melee.hpp"
#include <boost/assign/list_of.hpp>
#include <cassert>

sanguis::server::entities::projectiles::melee::melee(
	environment const &env,
	messages::pos_type const& center,
	team::type const team_,
	messages::space_unit const damage)
: projectile(
		env,
		center,
		messages::mu(0), // angle doesn't matter here
		team_,
		boost::assign::map_list_of
			(property::type::health, property(messages::mu(1)))
			(property::type::movement_speed, property(messages::mu(0))),
		dim_type(1, 1),
		static_cast<time_type>(1)), // short lifetime
  damage(damage)
{}

sanguis::entity_type::type
sanguis::server::entities::projectiles::melee::type() const
{
	return entity_type::indeterminate;
}

void sanguis::server::entities::projectiles::melee::do_hit(
	hit_vector const &hits)
{
	damage_array const damage_values =
		boost::assign::list_of
		(messages::mu(1))
		(messages::mu(0))
		(messages::mu(0))
		(messages::mu(0))
		(messages::mu(0));
	
	assert(!hits.empty());

	hits[0].get().damage(
		damage,
		damage_values);
	die();
}
