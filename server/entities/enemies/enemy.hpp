#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_ENEMY_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_ENEMY_HPP_INCLUDED

#include "../entity_with_weapon.hpp"
#include "../../ai/base.hpp"
#include "../../weapons/weapon.hpp"
#include "../../../enemy_type.hpp"

namespace sanguis
{
namespace server
{
namespace entities
{
namespace enemies
{

class enemy : public entity_with_weapon {
public:	
	enemy(
		enemy_type::type,
		environment const &,
		armor_array const &,
		messages::pos_type const &pos,
		messages::space_unit angle,
		messages::space_unit direction,
		property_map const &,
		ai::ai_ptr,
		weapons::weapon_ptr weapon,
		unsigned spawn_chance,
		messages::exp_type exp);

	void update(
		time_type,
		container &);

	enemy_type::type etype() const;
private:
	messages::auto_ptr add_message() const;
	entity_type::type type() const;
	messages::dim_type const dim() const;
	messages::exp_type exp() const;
	bool invulnerable() const;
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
