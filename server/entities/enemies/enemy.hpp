#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_ENEMY_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_ENEMY_HPP_INCLUDED

#include "../entity_with_ai.hpp"
#include "../../../enemy_type.hpp"

namespace sanguis
{
namespace server
{
namespace entities
{
namespace enemies
{

class enemy : public entity_with_ai {
public:	
	enemy(
		enemy_type::type,
		environment const &,
		armor_array const &,
		messages::pos_type const &center,
		messages::space_unit angle,
		messages::space_unit direction,
		property_map const &,
		ai::ai_ptr,
		weapons::weapon_ptr weapon,
		unsigned spawn_chance,
		messages::exp_type exp);

	enemy_type::type etype() const;
private:
	messages::auto_ptr add_message() const;
	messages::exp_type exp() const;
	void on_die();

	ai::ai_ptr         ai_;
	enemy_type::type   etype_;
	unsigned           spawn_chance;
	messages::exp_type exp_;
};

}
}
}
}

#endif
