#include "simple_bullet.hpp"
#include "../get_dim.hpp"
#include <boost/assign/list_of.hpp>

namespace
{

const sanguis::messages::space_unit bullet_speed(
	sanguis::messages::mu(200));

}

sanguis::server::projectiles::simple_bullet::simple_bullet(
	const send_callback &send_callback_,
	const insert_callback &insert_callback_,
	messages::pos_type const& pos,
	const messages::space_unit angle,
	const team::type team_,
	const messages::space_unit damage)
: projectile(
	send_callback_,
	insert_callback_,
	pos,
	angle,
	messages::mu(1),
	team_,
	messages::mu(1),
	bullet_speed,
	static_cast<time_type>(10)),
  damage(damage)
{}

sanguis::entity_type::type
sanguis::server::projectiles::simple_bullet::type() const
{
	return entity_type::bullet;
}

sanguis::messages::dim_type
sanguis::server::projectiles::simple_bullet::dim() const
{
	return get_dim(SGE_TEXT("bullet"), SGE_TEXT("default"));
}

void sanguis::server::projectiles::simple_bullet::do_hit(
	entity &target)
{
	const damage_array damage_values =
		boost::assign::list_of
		(messages::mu(0))
		(messages::mu(1))
		(messages::mu(0))
		(messages::mu(0))
		(messages::mu(0));
			
	target.damage(
		damage,
		damage_values);

	die();
}
