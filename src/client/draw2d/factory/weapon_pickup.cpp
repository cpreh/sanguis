#include "weapon_pickup.hpp"
#include "../entities/model/object.hpp"
#include "../z_ordering.hpp"
#include "../../../load/weapon_pickup_name.hpp"
#include <fcppt/make_unique_ptr.hpp>

sanguis::client::draw2d::entities::unique_ptr
sanguis::client::draw2d::factory::weapon_pickup(
	entities::model::parameters const &_param,
	weapon_type::type const _weapon
)
{
	return
		entities::unique_ptr(
			fcppt::make_unique_ptr<
				entities::model::object
			>(
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
