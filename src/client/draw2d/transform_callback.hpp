#ifndef SANGUIS_CLIENT_DRAW2D_TRANSFORM_CALLBACK_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_TRANSFORM_CALLBACK_HPP_INCLUDED

#include "sprite/center.hpp"
#include <fcppt/function/object_fwd.hpp>

namespace sanguis
{
namespace client
{
namespace draw2d
{

typedef fcppt::function::object<
	void (
		sprite::center const &
	)
> transform_callback;

}
}
}

#endif
