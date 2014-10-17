#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_PARAMETERS_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_PARAMETERS_HPP_INCLUDED

#include <sanguis/client/optional_health_pair.hpp>
#include <sanguis/client/draw2d/entities/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/order_vector.hpp>
#include <sanguis/client/draw2d/entities/model/decay_option.hpp>
#include <sanguis/client/draw2d/entities/model/parameters_fwd.hpp>
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
		sanguis::load::model::path const &,
		sanguis::client::draw2d::entities::order_vector const &,
		sanguis::client::optional_health_pair const &,
		sanguis::client::draw2d::entities::model::decay_option,
		sanguis::client::draw2d::sprite::normal::color
	);

	sanguis::client::draw2d::entities::load_parameters const &
	load_parameters() const;

	sanguis::load::model::path const &
	path() const;

	sanguis::client::draw2d::entities::order_vector const &
	orders() const;

	sanguis::client::optional_health_pair const &
	health_pair() const;

	sanguis::client::draw2d::entities::model::decay_option
	decay_option() const;

	sanguis::client::draw2d::sprite::normal::color const
	color() const;
private:
	sanguis::client::draw2d::entities::load_parameters const &load_parameters_;

	sanguis::load::model::path const &path_;

	sanguis::client::draw2d::entities::order_vector const &orders_;

	sanguis::client::optional_health_pair const health_pair_;

	sanguis::client::draw2d::entities::model::decay_option const decay_option_;

	sanguis::client::draw2d::sprite::normal::color const color_;
};

}
}
}
}
}

#endif
