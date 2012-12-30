#include <sanguis/weapon_type.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/entities/order_vector.hpp>
#include <sanguis/client/draw2d/entities/unique_ptr.hpp>
#include <sanguis/client/draw2d/entities/model/object.hpp>
#include <sanguis/client/draw2d/entities/model/parameters_fwd.hpp>
#include <sanguis/client/draw2d/factory/weapon_pickup.hpp>
#include <sanguis/load/weapon_pickup_name.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/assign/make_container.hpp>


sanguis::client::draw2d::entities::unique_ptr
sanguis::client::draw2d::factory::weapon_pickup(
	sanguis::client::draw2d::entities::model::parameters const &_param,
	sanguis::weapon_type const _weapon
)
{
	return
		sanguis::client::draw2d::entities::unique_ptr(
			fcppt::make_unique_ptr<
				sanguis::client::draw2d::entities::model::object
			>(
				_param,
				sanguis::load::weapon_pickup_name(
					_weapon
				),
				fcppt::assign::make_container<
					sanguis::client::draw2d::entities::order_vector
				>(
					z_ordering::pickup
				),
				entities::model::needs_healthbar::no,
				entities::model::decay_option::immediate
			)
		);
}
