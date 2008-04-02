#ifndef SANGUIS_SERVER_PLAYER_HPP_INCLUDED
#define SANGUIS_SERVER_PLAYER_HPP_INCLUDED

#include "entity.hpp"
#include "../net/types.hpp"
#include <sge/timer.hpp>
#include <sge/console/console.hpp>

namespace sanguis
{
namespace server
{
class player : public entity
{
	public:
	player(const entity_id,const net::id_type net_id,const messages::pos_type center,const messages::pos_type speed,
		const messages::space_unit angle,const messages::space_unit health);
	messages::pos_type center() const { return center_; } 
	messages::pos_type speed() const { return speed_; }
	messages::space_unit angle() const { return angle_; }
	messages::space_unit health() const { return health_; }
	void update(const time_type);
	bool spawn_bullet() const;
	net::id_type net_id() const { return net_id_; }
	private:
	static sge::con::var<messages::space_unit> bullet_frequency;

	mutable sge::timer shooting_timer;
	messages::pos_type center_,speed_;
	messages::space_unit angle_;
	net::id_type net_id_;
	bool shooting_;
	messages::space_unit health_;
};
}
}

#endif
