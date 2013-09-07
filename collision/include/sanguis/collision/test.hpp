#ifndef SANGUIS_COLLISION_TEST_HPP_INCLUDED
#define SANGUIS_COLLISION_TEST_HPP_INCLUDED

#include <sanguis/collision/center_fwd.hpp>
#include <sanguis/collision/dim2_fwd.hpp>
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
	sanguis::collision::dim2,
	sanguis::creator::grid const &
);

}
}

#endif
