#include "player.hpp"
#include "../load/model/collection.hpp"
#include "../load/model/singleton.hpp"
#include <sge/math/vec_dim.hpp>

sge::con::var<sanguis::messages::space_unit> sanguis::server::player::bullet_frequency(SGE_TEXT("player_bullet_freq"),static_cast<messages::space_unit>(0.5));
sge::con::var<sanguis::messages::space_unit> sanguis::server::player::running_speed(SGE_TEXT("player_speed"),static_cast<messages::space_unit>(0.1));

sanguis::server::player::player(const entity_id id,const net::id_type net_id_,
	const messages::pos_type center_,const messages::pos_type direction_,
	const messages::space_unit angle_,const messages::space_unit health_,
	const messages::space_unit max_health_,const messages::string &name_)
	: entity(id),
	  shooting_timer(static_cast<sge::timer::interval_type>(static_cast<messages::space_unit>(sge::second())*bullet_frequency.value())),
		direction_(direction_),
		pos_(center_ - dim()/static_cast<messages::space_unit>(2)),
		angle_(angle_),
		net_id_(net_id_),
		shooting_(false),
		health_(health_),
		max_health_(max_health_),
		name_(name_)
{}

bool sanguis::server::player::spawn_bullet() const
{
	return shooting_ && shooting_timer.update_b();
}

sanguis::messages::dim_type sanguis::server::player::dim() const
{
	return sge::math::structure_cast<messages::space_unit>(load::model::singleton()["player"]["bottom"][weapon_type::pistol][animation_type::walking].get().at(0).dim());
}

sanguis::messages::pos_type sanguis::server::player::speed() const
{
	return direction_ * running_speed.value();
}

void sanguis::server::player::shooting(const bool n)
{
	if (shooting_ == n)
		return;
	
	shooting_ = n;
	
	if (n)
		shooting_timer.reset();
}

void sanguis::server::player::update(const time_type delta)
{
	pos_ += speed() * delta;
}
