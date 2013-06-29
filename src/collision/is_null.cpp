#include <sanguis/collision/is_null.hpp>
#include <sanguis/collision/unit.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cmath>
#include <fcppt/config/external_end.hpp>


bool
sanguis::collision::is_null(
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
