#ifndef SANGUIS_CLIENT_DRAW2D_SUNLIGHT_LERP_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SUNLIGHT_LERP_HPP_INCLUDED

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace sunlight
{

template<
	typename T,
	typename Real
>
T const
lerp(
	T const &a,
	T const &b,
	Real const r
)
{
	return
		a + r * (b - a);
}

}
}
}
}

#endif
