#include "enemy.hpp"
#include "../entities/model/object.hpp"
#include "../z_ordering.hpp"
#include "../../../enemy_type.hpp"
#include "../../../load/enemy_name.hpp"

sanguis::client::draw2d::entities::auto_ptr
sanguis::client::draw2d::factory::enemy(
	entities::model::parameters const &_param,
	enemy_type::type const _etype
)
{
	return
		entities::auto_ptr(
			new entities::model::object(
				_param,
				load::enemy_name(
					_etype
				),
				z_ordering::model_generic,
				entities::model::needs_healthbar::no,
				entities::model::decay_option::delayed
			)
		);
}
