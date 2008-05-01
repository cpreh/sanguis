#ifndef SANGUIS_SERVER_ENTITIES_ENEMY_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMY_HPP_INCLUDED

#include "../entity_with_weapon.hpp"
#include "../ai/base.hpp"

namespace sanguis
{
namespace server
{
namespace entities
{

class enemy : public entity_with_weapon {
protected:
	enemy(
		environment const &,
		armor_array const &,
		messages::pos_type const &pos,
		messages::space_unit angle,
		messages::space_unit direction,
		messages::space_unit health,
		messages::space_unit max_health,
		team::type team,
		messages::space_unit speed,
		messages::space_unit max_speed,
		ai::ai_ptr);

	void update(
		time_type,
		entity_container &);
private:
	ai::ai_ptr ai_;
};

}
}
}

#endif
