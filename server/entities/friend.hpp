#ifndef SANGUIS_SERVER_ENTITIES_FRIEND_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_FRIEND_HPP_INCLUDED

#include "entity_with_ai.hpp"
#include "../../enemy_type.hpp"

namespace sanguis
{
namespace server
{
namespace entities
{

class friend_ : public entity_with_ai {
public:
	friend_(
		enemy_type::type,
		server::environment const &,
		armor_array const &,
		pos_type const &center,
		space_unit angle,
		space_unit direction,
		team::type,
		property_map const &,
		ai::auto_ptr,
		weapons::auto_ptr weapon);
private:
	messages::auto_ptr add_message() const;

	// TODO: we want to make a new type for this
	enemy_type::type const etype_;
};

}
}
}

#endif
