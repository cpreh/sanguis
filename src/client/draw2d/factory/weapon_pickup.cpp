#include <sanguis/weapon_type.hpp>
#include <sanguis/client/optional_health_pair.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/entities/order_vector.hpp>
#include <sanguis/client/draw2d/entities/unique_ptr.hpp>
#include <sanguis/client/draw2d/entities/model/decay_option.hpp>
#include <sanguis/client/draw2d/entities/model/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/model/name.hpp>
#include <sanguis/client/draw2d/entities/model/object.hpp>
#include <sanguis/client/draw2d/entities/model/parameters.hpp>
#include <sanguis/client/draw2d/factory/weapon_pickup.hpp>
#include <sanguis/load/weapon_pickup_name.hpp>
#include <fcppt/make_unique_ptr.hpp>


sanguis::client::draw2d::entities::unique_ptr
sanguis::client::draw2d::factory::weapon_pickup(
	sanguis::client::draw2d::entities::model::load_parameters const &_parameters,
	sanguis::weapon_type const _weapon_type
)
{
	return
		sanguis::client::draw2d::entities::unique_ptr(
			fcppt::make_unique_ptr<
				sanguis::client::draw2d::entities::model::object
			>(
				sanguis::client::draw2d::entities::model::parameters(
					_parameters,
					sanguis::client::draw2d::entities::model::name(
						sanguis::load::weapon_pickup_name(
							_weapon_type
						)
					),
					sanguis::client::draw2d::entities::order_vector{
						sanguis::client::draw2d::z_ordering::pickup
					},
					sanguis::client::optional_health_pair(),
					sanguis::client::draw2d::entities::model::decay_option::immediate
				)
			)
		);
}
