#include <sanguis/weapon_description.hpp>
#include <sanguis/client/optional_health_pair.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/entities/order_vector.hpp>
#include <sanguis/client/draw2d/entities/weapon_pickup.hpp>
#include <sanguis/client/draw2d/entities/hover/info.hpp>
#include <sanguis/client/draw2d/entities/hover/optional_info.hpp>
#include <sanguis/client/draw2d/entities/hover/weapon.hpp>
#include <sanguis/client/draw2d/entities/model/decay_option.hpp>
#include <sanguis/client/draw2d/entities/model/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/model/name.hpp>
#include <sanguis/client/draw2d/entities/model/object.hpp>
#include <sanguis/client/draw2d/entities/model/parameters.hpp>
#include <sanguis/load/weapon_pickup_name.hpp>


sanguis::client::draw2d::entities::weapon_pickup::weapon_pickup(
	sanguis::client::draw2d::entities::model::load_parameters const &_load_parameters,
	sanguis::weapon_description const &_weapon_description
)
:
	sanguis::client::draw2d::entities::model::object(
		sanguis::client::draw2d::entities::model::parameters(
			_load_parameters,
			sanguis::client::draw2d::entities::model::name(
				sanguis::load::weapon_pickup_name(
					_weapon_description.weapon_type()
				)
			),
			sanguis::client::draw2d::entities::order_vector{
				sanguis::client::draw2d::z_ordering::pickup
			},
			sanguis::client::optional_health_pair(),
			sanguis::client::draw2d::entities::model::decay_option::immediate
		)
	),
	weapon_description_(
		_weapon_description
	)
{
}

sanguis::client::draw2d::entities::weapon_pickup::~weapon_pickup()
{
}

sanguis::client::draw2d::entities::hover::optional_info
sanguis::client::draw2d::entities::weapon_pickup::hover() const
{
	return
		sanguis::client::draw2d::entities::hover::optional_info(
			sanguis::client::draw2d::entities::hover::info(
				sanguis::client::draw2d::entities::hover::weapon(
					weapon_description_
				)
			)
		);
}
