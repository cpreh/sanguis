#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_ORDER_FUNCTION_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_ORDER_FUNCTION_HPP_INCLUDED

#include <sanguis/client/draw2d/z_ordering_fwd.hpp>
#include <sanguis/client/draw2d/sprite/index_fwd.hpp>
#include <fcppt/function_impl.hpp>


namespace sanguis::client::draw2d::entities
{

using
order_function
=
fcppt::function<
	sanguis::client::draw2d::z_ordering (
		sanguis::client::draw2d::sprite::index
	)
>;

}

#endif
