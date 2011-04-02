#include "pos.hpp"
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/dim.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/math/dim/arithmetic.hpp>

sanguis::server::pos const
sanguis::server::entities::pos(
	server::center const &_center,
	server::dim const &_dim
)
{
	return
		server::pos(
			_center.get()
			- _dim
			/ static_cast<
				space_unit
			>(
				2
			)
		);
}
