#ifndef SANGUIS_COLLISION_TEST_HPP_INCLUDED
#define SANGUIS_COLLISION_TEST_HPP_INCLUDED

#include <sanguis/collision/center_fwd.hpp>
#include <sanguis/collision/radius_fwd.hpp>
#include <sanguis/collision/symbol.hpp>
#include <sanguis/creator/grid_fwd.hpp>


namespace sanguis
{
namespace collision
{

SANGUIS_COLLISION_SYMBOL
bool
test(
	sanguis::collision::center,
	sanguis::collision::radius,
	sanguis::creator::grid const &
);

}
}

#endif
