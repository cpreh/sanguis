#ifndef SANGUIS_SERVER_ENTITIES_ENEMIES_ENEMY_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENEMIES_ENEMY_HPP_INCLUDED

#include "../entity_with_ai.hpp"
#include "../../environment/load_context_ptr.hpp"
#include "../../probability_type.hpp"
#include "../../exp_type.hpp"
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
		server::environment::load_context_ptr,
		damage::armor const &,
		property_map const &,
		ai::auto_ptr,
		weapons::auto_ptr weapon,
		probability_type spawn_chance,
		exp_type exp
	);

	enemy_type::type etype() const;
private:
	messages::auto_ptr add_message() const;
	void on_die();

	enemy_type::type const etype_;
	probability_type const spawn_chance;
	exp_type const exp_;
};

}
}
}
}

#endif
