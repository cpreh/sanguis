#ifndef SANGUIS_SERVER_PLAYER_HPP_INCLUDED
#define SANGUIS_SERVER_PLAYER_HPP_INCLUDED

#include "entity.hpp"
#include "../net/types.hpp"
#include "../console_timer.hpp"
#include <sge/timer.hpp>
#include <sge/console/console.hpp>

namespace sanguis
{
namespace server
{
class player : public entity
{
	public:
	player(
		const net::id_type net_id,
		const messages::pos_type &center,
		const messages::space_unit direction,
		const messages::space_unit speed,
		const messages::space_unit angle,
		const messages::space_unit health,
		const messages::space_unit max_health,
		const messages::string &name);
	// virtual functions
	messages::dim_type dim() const;
	messages::space_unit max_speed() const;
	messages::space_unit health() const { return health_; }
	messages::space_unit max_health() const { return max_health_; }
	entity_type::type type() const { return entity_type::player; }
	ai_type::type ai_type() const { return ai_type::none; }

	// own functions
	void shooting(const bool);
	void attack(entity &);
	bool spawn_bullet() const;
	bool invulnerable() const;
	net::id_type net_id() const { return net_id_; }
	messages::string name() const { return name_; }

	private:
	static sge::con::var<messages::space_unit> bullet_frequency;
	static sge::con::var<messages::space_unit> running_speed;

	mutable console_timer shooting_timer;
	net::id_type net_id_;
	bool shooting_;
	messages::space_unit health_,max_health_;
	messages::string name_;
};
}
}

#endif
