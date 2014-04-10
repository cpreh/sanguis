#ifndef SANGUIS_CLIENT_DRAW2D_COLLIDE_CALLBACK_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_COLLIDE_CALLBACK_HPP_INCLUDED

#include <sanguis/client/draw2d/collide_parameters_fwd.hpp>
#include <sanguis/client/draw2d/optional_speed_fwd.hpp>
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
	sanguis::client::draw2d::optional_speed (
		sanguis::client::draw2d::collide_parameters const &
	)
> collide_callback;

}
}
}

#endif
