#include <sanguis/optional_primary_weapon_type.hpp>
#include <sanguis/weapon_status.hpp>
#include <sanguis/client/optional_health_pair.hpp>
#include <sanguis/client/draw2d/speed.hpp>
#include <sanguis/client/draw2d/entities/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/order_function.hpp>
#include <sanguis/client/draw2d/entities/model/decay_option.hpp>
#include <sanguis/client/draw2d/entities/model/parameters.hpp>
#include <sanguis/client/draw2d/sprite/center.hpp>
#include <sanguis/client/draw2d/sprite/rotation.hpp>
#include <sanguis/client/draw2d/sprite/normal/color.hpp>
#include <sanguis/load/model/path.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::client::draw2d::entities::model::parameters::parameters(
	sanguis::client::draw2d::entities::load_parameters const &_load_parameters,
	sanguis::load::model::path &&_path,
	sanguis::client::draw2d::entities::order_function const &_order_function,
	sanguis::client::optional_health_pair const &_health_pair,
	sanguis::client::draw2d::entities::model::decay_option const _decay_option,
	sanguis::optional_primary_weapon_type const _primary_weapon_type,
	sanguis::weapon_status const _weapon_status,
	sanguis::client::draw2d::speed const _speed,
	sanguis::client::draw2d::sprite::center const _center,
	sanguis::client::draw2d::sprite::rotation const _rotation,
	sanguis::client::draw2d::sprite::normal::color const _color
)
:
	load_parameters_(
		_load_parameters
	),
	path_(
		std::move(
			_path
		)
	),
	order_function_{
		std::move(
			_order_function
		)
	},
	health_pair_{
		_health_pair
	},
	decay_option_{
		_decay_option
	},
	primary_weapon_type_{
		_primary_weapon_type
	},
	weapon_status_{
		_weapon_status
	},
	speed_{
		_speed
	},
	center_{
		_center
	},
	rotation_{
		_rotation
	},
	color_{
		_color
	}
{
}

sanguis::client::draw2d::entities::load_parameters const &
sanguis::client::draw2d::entities::model::parameters::load_parameters() const
{
	return
		load_parameters_;
}

sanguis::load::model::path const &
sanguis::client::draw2d::entities::model::parameters::path() const
{
	return
		path_;
}

sanguis::client::draw2d::entities::order_function const &
sanguis::client::draw2d::entities::model::parameters::order_function() const
{
	return
		order_function_;
}

sanguis::client::optional_health_pair const &
sanguis::client::draw2d::entities::model::parameters::health_pair() const
{
	return
		health_pair_;
}

sanguis::client::draw2d::entities::model::decay_option
sanguis::client::draw2d::entities::model::parameters::decay_option() const
{
	return
		decay_option_;
}

sanguis::optional_primary_weapon_type const
sanguis::client::draw2d::entities::model::parameters::primary_weapon_type() const
{
	return
		primary_weapon_type_;
}

sanguis::weapon_status
sanguis::client::draw2d::entities::model::parameters::weapon_status() const
{
	return
		weapon_status_;
}

sanguis::client::draw2d::speed const
sanguis::client::draw2d::entities::model::parameters::speed() const
{
	return
		speed_;
}

sanguis::client::draw2d::sprite::center const
sanguis::client::draw2d::entities::model::parameters::center() const
{
	return
		center_;
}

sanguis::client::draw2d::sprite::rotation
sanguis::client::draw2d::entities::model::parameters::rotation() const
{
	return
		rotation_;
}

sanguis::client::draw2d::sprite::normal::color const
sanguis::client::draw2d::entities::model::parameters::color() const
{
	return
		color_;
}
