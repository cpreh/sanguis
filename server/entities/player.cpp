#include "player.hpp"
#include "../../load/model/collection.hpp"
#include "../../load/model/singleton.hpp"
#include <sge/math/vec_dim.hpp>

namespace
{
sge::con::var<sanguis::messages::space_unit> running_speed(SGE_TEXT("player_speed"),sanguis::messages::mu(60));
}

sanguis::server::entities::player::player(
	const net::id_type net_id_,
	const messages::pos_type &center_,
	const messages::space_unit direction_,
	const messages::space_unit speed_,
	const messages::space_unit angle_,
	const messages::space_unit health_,
	const messages::space_unit max_health_,
	const messages::string &name_)
	: entity(
			center_ - dim()/messages::mu(2),
			angle_,
			direction_,
			health_,
			max_health_,
			team::players,
			speed_,
			weapons::weapon_ptr()),
	  shooting_timer(SGE_TEXT("player_bullet_freq"),sge::su(0.5)),
		net_id_(net_id_),
		shooting_(false),
		health_(health_),
		max_health_(max_health_),
		name_(name_)
{}

void sanguis::server::entities::player::attack(entity &) {}

bool sanguis::server::entities::player::invulnerable() const
{
	return false;
}

sanguis::messages::dim_type sanguis::server::entities::player::dim() const
{
	return sge::math::structure_cast<messages::space_unit>(load::model::singleton()["player"]["bottom"][weapon_type::pistol][animation_type::walking].get().dim());
}

sanguis::messages::space_unit sanguis::server::entities::player::max_speed() const
{
	return running_speed.value();
}

void sanguis::server::entities::player::shooting(const bool n)
{
	shooting_ = n;
}

void sanguis::server::entities::player::update(
	const time_type delta)
{
	entity::update(delta);
}
