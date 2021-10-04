#ifndef SANGUIS_COLLISION_IMPL_IS_NULL_HPP_INCLUDED
#define SANGUIS_COLLISION_IMPL_IS_NULL_HPP_INCLUDED

#include <sanguis/collision/unit.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cmath>
#include <fcppt/config/external_end.hpp>


namespace sanguis::collision::impl
{

inline
bool
is_null(
	sanguis::collision::unit const _unit
)
{
	constexpr sanguis::collision::unit const epsilon{0.001F};

	return
		std::abs(
			_unit
		)
		<
		epsilon
		;
}

}

#endif
