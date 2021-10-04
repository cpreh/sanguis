#ifndef SANGUIS_CLIENT_DRAW2D_COLLIDE_CALLBACK_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_COLLIDE_CALLBACK_HPP_INCLUDED

#include <sanguis/client/draw2d/collide_parameters_fwd.hpp>
#include <sanguis/client/draw2d/optional_speed_fwd.hpp>
#include <fcppt/function_impl.hpp>


namespace sanguis::client::draw2d
{

using
collide_callback
=
fcppt::function<
	sanguis::client::draw2d::optional_speed (
		sanguis::client::draw2d::collide_parameters const &
	)
>;

}

#endif
