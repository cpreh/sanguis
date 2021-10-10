#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_CONSTANT_ORDER_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_CONSTANT_ORDER_HPP_INCLUDED

#include <sanguis/client/draw2d/z_ordering_fwd.hpp>
#include <sanguis/client/draw2d/entities/order_function.hpp>

namespace sanguis::client::draw2d::entities
{

sanguis::client::draw2d::entities::order_function
    constant_order(sanguis::client::draw2d::z_ordering);

}

#endif
