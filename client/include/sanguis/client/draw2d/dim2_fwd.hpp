#ifndef SANGUIS_CLIENT_DRAW2D_DIM2_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_DIM2_FWD_HPP_INCLUDED

#include <sanguis/client/draw2d/funit.hpp>
#include <fcppt/math/dim/static_fwd.hpp>


namespace sanguis::client::draw2d
{

using
dim2
=
fcppt::math::dim::static_<
	sanguis::client::draw2d::funit,
	2
>;

}

#endif
