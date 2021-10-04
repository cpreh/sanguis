#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_PARAMETERS_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_PARAMETERS_HPP_INCLUDED

#include <sanguis/optional_primary_weapon_type.hpp>
#include <sanguis/weapon_status.hpp>
#include <sanguis/client/optional_health_pair.hpp>
#include <sanguis/client/draw2d/speed.hpp>
#include <sanguis/client/draw2d/entities/load_parameters.hpp>
#include <sanguis/client/draw2d/entities/order_function.hpp>
#include <sanguis/client/draw2d/entities/model/decay_option.hpp>
#include <sanguis/client/draw2d/entities/model/parameters_fwd.hpp>
#include <sanguis/client/draw2d/sprite/center.hpp>
#include <sanguis/client/draw2d/sprite/rotation.hpp>
#include <sanguis/client/draw2d/sprite/normal/color.hpp>
#include <sanguis/load/model/path.hpp>


namespace sanguis::client::draw2d::entities::model
{

class parameters
{
public:
	parameters(
		sanguis::client::draw2d::entities::load_parameters const &,
		sanguis::load::model::path &&,
		sanguis::client::draw2d::entities::order_function &&,
		sanguis::client::optional_health_pair const &,
		sanguis::client::draw2d::entities::model::decay_option,
		sanguis::optional_primary_weapon_type,
		sanguis::weapon_status,
		sanguis::client::draw2d::speed,
		sanguis::client::draw2d::sprite::center,
		sanguis::client::draw2d::sprite::rotation,
		sanguis::client::draw2d::sprite::normal::color
	);

	[[nodiscard]]
	sanguis::client::draw2d::entities::load_parameters const &
	load_parameters() const;

	[[nodiscard]]
	sanguis::load::model::path const &
	path() const;

	[[nodiscard]]
	sanguis::client::draw2d::entities::order_function const &
	order_function() const;

	[[nodiscard]]
	sanguis::client::optional_health_pair const &
	health_pair() const;

	[[nodiscard]]
	sanguis::client::draw2d::entities::model::decay_option
	decay_option() const;

	[[nodiscard]]
	sanguis::optional_primary_weapon_type
	primary_weapon_type() const;

	[[nodiscard]]
	sanguis::weapon_status
	weapon_status() const;

	[[nodiscard]]
	sanguis::client::draw2d::speed
	speed() const;

	[[nodiscard]]
	sanguis::client::draw2d::sprite::center
	center() const;

	[[nodiscard]]
	sanguis::client::draw2d::sprite::rotation
	rotation() const;

	[[nodiscard]]
	sanguis::client::draw2d::sprite::normal::color
	color() const;
private:
	sanguis::client::draw2d::entities::load_parameters load_parameters_;

	sanguis::load::model::path path_;

	sanguis::client::draw2d::entities::order_function order_function_;

	sanguis::client::optional_health_pair health_pair_;

	sanguis::client::draw2d::entities::model::decay_option decay_option_;

	sanguis::optional_primary_weapon_type primary_weapon_type_;

	sanguis::weapon_status weapon_status_;

	sanguis::client::draw2d::speed speed_;

	sanguis::client::draw2d::sprite::center center_;

	sanguis::client::draw2d::sprite::rotation rotation_;

	sanguis::client::draw2d::sprite::normal::color color_;
};

}

#endif
