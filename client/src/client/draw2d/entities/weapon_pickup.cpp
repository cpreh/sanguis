#include <sanguis/optional_primary_weapon_type.hpp>
#include <sanguis/weapon_description.hpp>
#include <sanguis/weapon_status.hpp>
#include <sanguis/client/optional_health_pair.hpp>
#include <sanguis/client/draw2d/speed.hpp>
#include <sanguis/client/draw2d/z_ordering.hpp>
#include <sanguis/client/draw2d/entities/constant_order.hpp>
#include <sanguis/client/draw2d/entities/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/weapon_pickup.hpp>
#include <sanguis/client/draw2d/entities/hover/info.hpp>
#include <sanguis/client/draw2d/entities/hover/optional_info.hpp>
#include <sanguis/client/draw2d/entities/hover/variant.hpp>
#include <sanguis/client/draw2d/entities/hover/weapon.hpp>
#include <sanguis/client/draw2d/entities/model/decay_option.hpp>
#include <sanguis/client/draw2d/entities/model/object.hpp>
#include <sanguis/client/draw2d/entities/model/parameters.hpp>
#include <sanguis/client/draw2d/sprite/center.hpp>
#include <sanguis/client/draw2d/sprite/rotation.hpp>
#include <sanguis/client/draw2d/sprite/normal/white.hpp>
#include <sanguis/load/model/weapon_pickup_path.hpp>
#include <fcppt/math/vector/null.hpp>


sanguis::client::draw2d::entities::weapon_pickup::weapon_pickup(
	sanguis::client::draw2d::entities::load_parameters const &_load_parameters,
	sanguis::client::draw2d::sprite::center const _center,
	sanguis::client::draw2d::sprite::rotation const _rotation,
	sanguis::weapon_description const &_weapon_description
)
:
	sanguis::client::draw2d::entities::model::object(
		sanguis::client::draw2d::entities::model::parameters(
			_load_parameters,
			sanguis::load::model::weapon_pickup_path(
				_weapon_description.weapon_type()
			),
			sanguis::client::draw2d::entities::constant_order(
				sanguis::client::draw2d::z_ordering::pickup
			),
			sanguis::client::optional_health_pair(),
			sanguis::client::draw2d::entities::model::decay_option::immediate,
			sanguis::optional_primary_weapon_type{},
			sanguis::weapon_status::nothing,
			sanguis::client::draw2d::speed{
				fcppt::math::vector::null<
					sanguis::client::draw2d::speed::value_type
				>()
			},
			_center,
			_rotation,
			sanguis::client::draw2d::sprite::normal::white()
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
				sanguis::client::draw2d::entities::hover::variant(
					sanguis::client::draw2d::entities::hover::weapon(
						weapon_description_
					)
				)
			)
		);
}
