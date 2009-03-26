#include "distance.hpp"
#include "../entities/entity.hpp"
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/vector/arithmetic.hpp>
#include <sge/math/vector/length.hpp>

sanguis::server::space_unit
sanguis::server::collision::distance(
	entities::entity const &a,
	entities::entity const &b)
{
	return distance(a, b.center());
}

sanguis::server::space_unit
sanguis::server::collision::distance(
	entities::entity const &a,
	pos_type const &b)
{
	return length(a.center() - b);
}
