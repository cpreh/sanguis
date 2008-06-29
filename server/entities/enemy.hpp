#ifndef SANGUIS_SERVER_ENTITIES_ENEMY_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMY_HPP_INCLUDED

#include "entity_with_weapon.hpp"
#include "../ai/base.hpp"
#include "../../enemy_type.hpp"

namespace sanguis
{
namespace server
{
namespace entities
{

class enemy : public entity_with_weapon {
public:	
	enemy_type::type etype() const;
protected:
	enemy(
		enemy_type::type,
		environment const &,
		armor_array const &,
		messages::pos_type const &pos,
		messages::space_unit angle,
		messages::space_unit direction,
		team::type team,
		property_map const &,
		ai::ai_ptr);

	void update(
		time_type,
		container &);
private:
	messages::base *add_message() const;

	entity_type::type type() const;

	void on_die();

	ai::ai_ptr       ai_;
	enemy_type::type etype_;
};

}
}
}

#endif
