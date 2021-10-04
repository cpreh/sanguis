#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_ORDER_FUNCTION_FROM_VECTOR_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_ORDER_FUNCTION_FROM_VECTOR_HPP_INCLUDED

#include <sanguis/client/draw2d/z_ordering_vector.hpp>
#include <sanguis/client/draw2d/entities/order_function.hpp>


namespace sanguis::client::draw2d::entities
{

sanguis::client::draw2d::entities::order_function
order_function_from_vector(
	sanguis::client::draw2d::z_ordering_vector &&
);

}

#endif
