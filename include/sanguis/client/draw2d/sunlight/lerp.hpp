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
	T const &_a,
	T const &_b,
	Real const _r
)
{
	return
		_a + _r * (_b - _a);
}

}
}
}
}

#endif
