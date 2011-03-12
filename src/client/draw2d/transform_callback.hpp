#ifndef SANGUIS_CLIENT_DRAW2D_TRANSFORM_CALLBACK_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_TRANSFORM_CALLBACK_HPP_INCLUDED

#include "sprite/point.hpp"
#include <fcppt/function/object_fwd.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{

typedef fcppt::function::object<
	void (
		sprite::point const &
	)
> transform_callback;

}
}
}

#endif
