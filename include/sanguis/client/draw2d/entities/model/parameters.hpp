#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_PARAMETERS_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_PARAMETERS_HPP_INCLUDED

#include <sanguis/client/draw2d/entities/order_vector.hpp>
#include <sanguis/client/draw2d/entities/model/decay_option.hpp>
#include <sanguis/client/draw2d/entities/model/load_parameters_fwd.hpp>
#include <sanguis/client/draw2d/entities/model/name.hpp>
#include <sanguis/client/draw2d/entities/model/optional_health_pair.hpp>
#include <sanguis/client/draw2d/entities/model/parameters_fwd.hpp>


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
		sanguis::client::draw2d::entities::model::load_parameters const &,
		sanguis::client::draw2d::entities::model::name const &,
		sanguis::client::draw2d::entities::order_vector const &,
		sanguis::client::draw2d::entities::model::optional_health_pair const &,
		sanguis::client::draw2d::entities::model::decay_option
	);

	sanguis::client::draw2d::entities::model::load_parameters const &
	load_parameters() const;

	sanguis::client::draw2d::entities::model::name const &
	name() const;

	sanguis::client::draw2d::entities::order_vector const &
	orders() const;

	sanguis::client::draw2d::entities::model::optional_health_pair const &
	health_pair() const;

	sanguis::client::draw2d::entities::model::decay_option
	decay_option() const;
private:
	sanguis::client::draw2d::entities::model::load_parameters const &load_parameters_;

	sanguis::client::draw2d::entities::model::name const &name_;

	sanguis::client::draw2d::entities::order_vector const &orders_;

	sanguis::client::draw2d::entities::model::optional_health_pair const health_pair_;

	sanguis::client::draw2d::entities::model::decay_option const decay_option_;
};

}
}
}
}
}

#endif
