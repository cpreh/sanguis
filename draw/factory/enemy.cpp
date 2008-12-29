#include "enemy.hpp"
#include "../model.hpp"
#include "../z_ordering.hpp"
#include "../../load/enemy_name.hpp"
#include "../../enemy_type.hpp"

sanguis::draw::entity_auto_ptr
sanguis::draw::factory::enemy(
	environment const &env,
	entity_id const id,
	enemy_type::type const etype)
{
	return entity_auto_ptr(
		new model(
			env,
			id,
			load::enemy_name(
				etype),
			z_ordering::model_generic));
}
