#include "bullet.hpp"
#include "../load/model/collection.hpp"
#include "../load/model/singleton.hpp"
#include "../resolution.hpp"
#include <sge/console/console.hpp>
#include <sge/math/rect_impl.hpp>
#include <sge/math/vec_dim.hpp>
#include <sge/math/rect_util.hpp>

namespace
{
sge::con::var<sanguis::messages::space_unit> bullet_speed(SGE_TEXT("bullet_speed"),sanguis::messages::mu(200));
sge::con::var<sanguis::messages::space_unit> bullet_damage(SGE_TEXT("bullet_damage"),sanguis::messages::mu(2));
}

sanguis::server::bullet::bullet(const messages::pos_type &center_,const messages::space_unit direction_,const messages::space_unit angle_) 
	: entity(
			center_ - dim()/messages::mu(2),
			angle_,
			direction_,
			messages::mu(1),
			messages::mu(1),
			team::players,
			messages::mu(1))
{}

bool sanguis::server::bullet::invulnerable() const { return true; }

void sanguis::server::bullet::attack(entity &e)
{
	// don't attack same team
	if (team() == e.team())
		return;
	
	e.health(e.health() - bullet_damage.value());
	health(messages::mu(-1));
}

sanguis::messages::dim_type sanguis::server::bullet::dim() const
{
	return sge::math::structure_cast<messages::space_unit>(load::model::singleton()["bullet"]["default"][weapon_type::none][animation_type::none].get().dim());
}

sanguis::messages::space_unit sanguis::server::bullet::max_speed() const
{
	return bullet_speed.value();
}

void sanguis::server::bullet::update(const time_type)
{
	// bullet not visible anymore?
	if (!sge::math::intersects(
		sge::math::rect(
			sge::su(-0.5)*sge::su(resolution().w()),
			sge::su(-0.5)*sge::su(resolution().h()),
			sge::su(1.5)*sge::su(resolution().w()),
			sge::su(1.5)*sge::su(resolution().h())),
		sge::math::structure_cast<sge::space_unit>(center())))
		health(messages::mu(-1));
}
