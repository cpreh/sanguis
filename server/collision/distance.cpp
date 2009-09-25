#include "distance.hpp"
#include "../entities/base.hpp"
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/vector/arithmetic.hpp>
#include <sge/math/vector/length.hpp>

sanguis::server::space_unit
sanguis::server::collision::distance(
	entities::base const &a,
	entities::base const &b
)
{
	return distance(a, b.center());
}

sanguis::server::space_unit
sanguis::server::collision::distance(
	entities::base const &a,
	pos_type const &b
)
{
	return distance(a.center(), b);
}

sanguis::server::space_unit
sanguis::server::collision::distance(
	pos_type const &a,
	pos_type const &b
)
{
	return length(a - b);
}
