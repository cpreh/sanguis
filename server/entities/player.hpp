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
		environment const &,
		armor_array const &,
		net::id_type const net_id,
		messages::pos_type const &center,
		messages::space_unit const direction,
		messages::space_unit const speed,
		messages::space_unit const angle,
		messages::space_unit const health,
		messages::space_unit const max_health,
		messages::string const &name);
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
