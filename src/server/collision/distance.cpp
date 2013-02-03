#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/vector.hpp>
#include <sanguis/server/collision/distance.hpp>
#include <sanguis/server/entities/base.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/length.hpp>


sanguis::server::space_unit
sanguis::server::collision::distance(
	sanguis::server::entities::base const &_a,
	sanguis::server::entities::base const &_b
)
{
	return
		sanguis::server::collision::distance(
			_a,
			_b.center().get()
		);
}

sanguis::server::space_unit
sanguis::server::collision::distance(
	sanguis::server::entities::base const &_a,
	sanguis::server::vector const &_b
)
{
	return
		sanguis::server::collision::distance(
			_a.center().get(),
			_b
		);
}

sanguis::server::space_unit
sanguis::server::collision::distance(
	sanguis::server::vector const &_a,
	sanguis::server::vector const &_b
)
{
	return
		fcppt::math::vector::length(
			_a
			- _b
		);
}
