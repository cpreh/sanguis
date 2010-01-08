#include "weapon_pickup.hpp"
#include "../entities/model/object.hpp"
#include "../z_ordering.hpp"
#include "../../load/weapon_pickup_name.hpp"

sanguis::client::draw2d::entities::auto_ptr
sanguis::client::draw2d::factory::weapon_pickup(
	entities::model::parameters const &param_,
	weapon_type::type const wtype
)
{
	return entities::auto_ptr(
		new entities::model::object(
			param_,
			load::weapon_pickup_name(
				wtype
			),
			z_ordering::pickup,
			false
		)	
	);
}
