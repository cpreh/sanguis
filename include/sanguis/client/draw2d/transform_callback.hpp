#ifndef SANGUIS_CLIENT_DRAW2D_TRANSFORM_CALLBACK_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_TRANSFORM_CALLBACK_HPP_INCLUDED

#include <sanguis/client/draw2d/sprite/center.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{

typedef std::function<
	void (
		sanguis::client::draw2d::sprite::center const &
	)
> transform_callback;

}
}
}

#endif
