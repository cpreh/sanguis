#ifndef SANGUIS_CLIENT_DRAW2D_COLLIDE_CALLBACK_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_COLLIDE_CALLBACK_HPP_INCLUDED

#include <sanguis/client/draw2d/sprite/center_fwd.hpp>
#include <sanguis/client/draw2d/sprite/dim_fwd.hpp>
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
	bool (
		sanguis::client::draw2d::sprite::center const &,
		sanguis::client::draw2d::sprite::dim const &
	)
> collide_callback;

}
}
}

#endif
