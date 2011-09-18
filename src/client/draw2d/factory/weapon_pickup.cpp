#include <sanguis/client/draw2d/factory/weapon_pickup.hpp>
#include <sanguis/client/draw2d/entities/model/object.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/load/weapon_pickup_name.hpp>
#include <fcppt/cref.hpp>
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
				fcppt::cref(
					_param
				),
				load::weapon_pickup_name(
					_weapon
				),
				z_ordering::pickup,
				entities::model::needs_healthbar::no,
				entities::model::decay_option::immediate
			)
		);
}
