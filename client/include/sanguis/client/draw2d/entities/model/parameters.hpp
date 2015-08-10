#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_PARAMETERS_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_PARAMETERS_HPP_INCLUDED

#include <sanguis/optional_primary_weapon_type.hpp>
#include <sanguis/weapon_status.hpp>
#include <sanguis/client/optional_health_pair.hpp>
#include <sanguis/client/draw2d/speed.hpp>
#include <sanguis/client/draw2d/entities/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/order_function.hpp>
#include <sanguis/client/draw2d/entities/model/decay_option.hpp>
#include <sanguis/client/draw2d/entities/model/parameters_fwd.hpp>
#include <sanguis/client/draw2d/sprite/center.hpp>
#include <sanguis/client/draw2d/sprite/rotation.hpp>
#include <sanguis/client/draw2d/sprite/normal/color.hpp>
#include <sanguis/load/model/path.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{
namespace model
{

class parameters
{
	FCPPT_NONASSIGNABLE(
		parameters
	);
public:
	parameters(
		sanguis::client::draw2d::entities::load_parameters const &,
		sanguis::load::model::path &&,
		sanguis::client::draw2d::entities::order_function const &,
		sanguis::client::optional_health_pair const &,
		sanguis::client::draw2d::entities::model::decay_option,
		sanguis::optional_primary_weapon_type,
		sanguis::weapon_status,
		sanguis::client::draw2d::speed,
		sanguis::client::draw2d::sprite::center,
		sanguis::client::draw2d::sprite::rotation,
		sanguis::client::draw2d::sprite::normal::color
	);

	sanguis::client::draw2d::entities::load_parameters const &
	load_parameters() const;

	sanguis::load::model::path const &
	path() const;

	sanguis::client::draw2d::entities::order_function const &
	order_function() const;

	sanguis::client::optional_health_pair const &
	health_pair() const;

	sanguis::client::draw2d::entities::model::decay_option
	decay_option() const;

	sanguis::optional_primary_weapon_type const
	primary_weapon_type() const;

	sanguis::weapon_status
	weapon_status() const;

	sanguis::client::draw2d::speed const
	speed() const;

	sanguis::client::draw2d::sprite::center const
	center() const;

	sanguis::client::draw2d::sprite::rotation
	rotation() const;

	sanguis::client::draw2d::sprite::normal::color const
	color() const;
private:
	sanguis::client::draw2d::entities::load_parameters const &load_parameters_;

	sanguis::load::model::path const path_;

	sanguis::client::draw2d::entities::order_function const order_function_;

	sanguis::client::optional_health_pair const health_pair_;

	sanguis::client::draw2d::entities::model::decay_option const decay_option_;

	sanguis::optional_primary_weapon_type const primary_weapon_type_;

	sanguis::weapon_status const weapon_status_;

	sanguis::client::draw2d::speed const speed_;

	sanguis::client::draw2d::sprite::center const center_;

	sanguis::client::draw2d::sprite::rotation const rotation_;

	sanguis::client::draw2d::sprite::normal::color const color_;
};

}
}
}
}
}

#endif
