#ifndef SANGUIS_SERVER_ENTITIES_PLAYER_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_PLAYER_HPP_INCLUDED

#include "entity_with_weapon.hpp"
#include "../../messages/types.hpp"
#include "../../net/types.hpp"

namespace sanguis
{
namespace server
{
namespace entities
{

class player : public entity_with_weapon {
public:
	player(
		environment const &,
		armor_array const &,
		net::id_type net_id,
		messages::pos_type const &center,
		messages::space_unit direction,
		messages::space_unit angle,
		property_map const &,
		messages::string const &name);

	// own functions
	net::id_type net_id() const;
	messages::string name() const;
	messages::exp_type exp() const;
	void exp(messages::exp_type);
	messages::level_type level() const;
	messages::level_type level_delta() const;

private:
	net::id_type net_id_;
	messages::string name_;
	messages::exp_type exp_;
	messages::level_type level_,
	                     level_delta_;
};

}
}
}

#endif
