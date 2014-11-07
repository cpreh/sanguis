#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_ORDER_VECTOR_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_ORDER_VECTOR_HPP_INCLUDED

#include <sanguis/client/draw2d/z_ordering.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{

typedef
std::vector<
	sanguis::client::draw2d::z_ordering
>
order_vector;

}
}
}
}

#endif
