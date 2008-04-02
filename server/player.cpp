#include "player.hpp"

sge::con::var<sanguis::messages::space_unit> sanguis::server::player::bullet_frequency(SGE_TEXT("player_bullet_freq"),static_cast<messages::space_unit>(0.5));

sanguis::server::player::player(const entity_id id,const net::id_type net_id_,
	const messages::pos_type center_,const messages::pos_type speed_,
	const messages::space_unit angle_,const messages::space_unit health_)
	: entity(id),
	  shooting_timer(static_cast<sge::timer::interval_type>(static_cast<messages::space_unit>(sge::second())*bullet_frequency.value())),
		center_(center_),
		speed_(speed_),
		angle_(angle_),
		net_id_(net_id_),
		shooting_(false),
		health_(health_)
{}

bool sanguis::server::player::spawn_bullet() const
{
	return shooting_ && shooting_timer.update_b();
}

void sanguis::server::player::update(const time_type delta)
{
	center_ += speed_ * delta;
}
