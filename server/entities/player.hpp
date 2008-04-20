#ifndef SANGUIS_SERVER_ENTITIES_PLAYER_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PLAYER_HPP_INCLUDED

#include "../entity_with_weapon.hpp"
#include "../../net/types.hpp"
#include <sge/timer.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{
class player : public entity_with_weapon
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
	entity_type::type type() const;

	// own functions
	void attack(entity &);
	bool invulnerable() const;
	net::id_type net_id() const;
	messages::string name() const;

	private:

	net::id_type net_id_;
	messages::string name_;
};
}
}
}

#endif
