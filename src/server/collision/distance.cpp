#include <sanguis/server/collision/distance.hpp>
#include <sanguis/server/entities/base.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/length.hpp>

sanguis::server::space_unit
sanguis::server::collision::distance(
	entities::base const &_a,
	entities::base const &_b
)
{
	return
		collision::distance(
			_a,
			_b.center().get()
		);
}

sanguis::server::space_unit
sanguis::server::collision::distance(
	entities::base const &_a,
	server::vector const &_b
)
{
	return
		collision::distance(
			_a.center().get(),
			_b
		);
}

sanguis::server::space_unit
sanguis::server::collision::distance(
	server::vector const &_a,
	server::vector const &_b
)
{
	return
		fcppt::math::vector::length(
			_a
			- _b
		);
}
