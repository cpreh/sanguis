#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_EXPAND_ORDERS_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_MODEL_EXPAND_ORDERS_HPP_INCLUDED

#include <sanguis/client/draw2d/entities/order_vector.hpp>
#include <sanguis/client/load/model/part_map.hpp>


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

sanguis::client::draw2d::entities::order_vector
expand_orders(
	sanguis::client::draw2d::entities::order_vector,
	sanguis::client::load::model::part_map::size_type
);

}
}
}
}
}

#endif
