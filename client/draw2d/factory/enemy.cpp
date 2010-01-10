#include "enemy.hpp"
#include "../entities/model/object.hpp"
#include "../z_ordering.hpp"
#include "../../../enemy_type.hpp"
#include "../../../load/enemy_name.hpp"

sanguis::client::draw2d::entities::auto_ptr
sanguis::client::draw2d::factory::enemy(
	entities::model::parameters const &param_,
	enemy_type::type const etype
)
{
	return entities::auto_ptr(
		new entities::model::object(
			param_,
			load::enemy_name(
				etype
			),
			z_ordering::model_generic,
			entities::model::needs_healthbar::no,
			entities::model::decay_option::delayed
		)
	);
}
