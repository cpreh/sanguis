#ifndef SANGUIS_CLIENT_DRAW2D_DIM2_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_DIM2_FWD_HPP_INCLUDED

#include <sanguis/client/draw2d/funit.hpp>
#include <fcppt/math/dim/static.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{

typedef fcppt::math::dim::static_<
	sanguis::client::draw2d::funit,
	2
> dim2;

}
}
}

#endif
