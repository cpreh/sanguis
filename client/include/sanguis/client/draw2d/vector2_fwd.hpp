#ifndef SANGUIS_CLIENT_DRAW2D_VECTOR2_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_VECTOR2_FWD_HPP_INCLUDED

#include <sanguis/client/draw2d/funit.hpp>
#include <fcppt/math/vector/static_fwd.hpp>


namespace sanguis::client::draw2d
{

using
vector2
=
fcppt::math::vector::static_<
	sanguis::client::draw2d::funit,
	2
>;

}

#endif
