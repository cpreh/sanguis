#include "zombie.hpp"
#include "../load/model/collection.hpp"
#include "../load/model/singleton.hpp"
#include <sge/math/vec_dim.hpp>

namespace
{
sge::con::var<sanguis::messages::space_unit> running_speed(SGE_TEXT("zombie_speed"),sanguis::messages::mu(40));
sge::con::var<sanguis::messages::space_unit> zombie_damage(SGE_TEXT("zombie_damage"),sanguis::messages::mu(10));
}

sanguis::server::zombie::zombie(
	const entity_id id,
	const messages::pos_type &center_,
	const messages::space_unit direction_,
	const messages::space_unit speed_,
	const messages::space_unit angle_,
	const messages::space_unit health_,
	const messages::space_unit max_health_)
	: entity(
			id,
			center_ - dim()/messages::mu(2),
			angle_,
			direction_,
			health_,
			max_health_,
			team::monsters,
			speed_)
{}

bool sanguis::server::zombie::invulnerable() const
{
	return false;
}

void sanguis::server::zombie::attack(entity &e)
{
	// don't attack invulnerable entities (makes no sense ;))
	if (e.invulnerable())
		return;
	
	e.health(e.health() - zombie_damage.value());
}

sanguis::messages::dim_type sanguis::server::zombie::dim() const
{
	return sge::math::structure_cast<messages::space_unit>(load::model::singleton()["zombie00"]["default"][weapon_type::none][animation_type::walking].get().dim());
}

sanguis::messages::space_unit sanguis::server::zombie::max_speed() const
{
	return running_speed.value();
}
