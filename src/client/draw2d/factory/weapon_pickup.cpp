#include "weapon_pickup.hpp"
#include "../entities/model/object.hpp"
#include "../z_ordering.hpp"
#include "../../../load/weapon_pickup_name.hpp"

sanguis::client::draw2d::entities::auto_ptr
sanguis::client::draw2d::factory::weapon_pickup(
	entities::model::parameters const &_param,
	weapon_type::type const _weapon
)
{
	return
		entities::auto_ptr(
			new entities::model::object(
				_param,
				load::weapon_pickup_name(
					_weapon
				),
				z_ordering::pickup,
				entities::model::needs_healthbar::no,
				entities::model::decay_option::immediate
			)	
		);
}
