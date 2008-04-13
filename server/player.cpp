#include "player.hpp"
#include "../load/model/collection.hpp"
#include "../load/model/singleton.hpp"
#include <sge/math/vec_dim.hpp>

sge::con::var<sanguis::messages::space_unit> sanguis::server::player::running_speed(SGE_TEXT("player_speed"),messages::mu(60));

sanguis::server::player::player(
	const entity_id id,
	const net::id_type net_id_,
	const messages::pos_type &center_,
	const messages::space_unit direction_,
	const messages::space_unit speed_,
	const messages::space_unit angle_,
	const messages::space_unit health_,
	const messages::space_unit max_health_,
	const messages::string &name_)
	: entity(
			id,
			center_ - dim()/messages::mu(2),
			angle_,
			direction_,
			messages::mu(1),
			messages::mu(1),
			speed_),
	  shooting_timer(SGE_TEXT("player_bullet_freq"),sge::su(0.5)),
		net_id_(net_id_),
		shooting_(false),
		health_(health_),
		max_health_(max_health_),
		name_(name_)
{}

bool sanguis::server::player::spawn_bullet() const
{
	return shooting_ && shooting_timer.v().update_b();
}

sanguis::messages::dim_type sanguis::server::player::dim() const
{
	return sge::math::structure_cast<messages::space_unit>(load::model::singleton()["player"]["bottom"][weapon_type::pistol][animation_type::walking].get().dim());
}

sanguis::messages::space_unit sanguis::server::player::max_speed() const
{
	return running_speed.value();
}

void sanguis::server::player::shooting(const bool n)
{
	if (shooting_ == n)
		return;
	
	shooting_ = n;
	
	if (n)
		shooting_timer.v().reset();
}
