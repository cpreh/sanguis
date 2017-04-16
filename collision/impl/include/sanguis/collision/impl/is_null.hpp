#ifndef SANGUIS_COLLISION_IMPL_IS_NULL_HPP_INCLUDED
#define SANGUIS_COLLISION_IMPL_IS_NULL_HPP_INCLUDED

#include <sanguis/collision/unit.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cmath>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace collision
{
namespace impl
{

inline
bool
is_null(
	sanguis::collision::unit const _unit
)
{
	return
		std::abs(
			_unit
		)
		<
		0.001f
		;
}

}
}
}

#endif
