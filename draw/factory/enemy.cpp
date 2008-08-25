#include "enemy.hpp"
#include "../model.hpp"
#include "../z_ordering.hpp"
#include "../../load/enemy_name.hpp"
#include "../../enemy_type.hpp"

sanguis::draw::factory::entity_ptr
sanguis::draw::factory::enemy(
	entity_id const id,
	system &sys,
	enemy_type::type const etype)
{
	return entity_ptr(
		new model(
			id,
			sys,
			load::enemy_name(
				etype),
			z_ordering::model_generic));
}
