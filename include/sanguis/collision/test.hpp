#ifndef SANGUIS_COLLISION_TEST_HPP_INCLUDED
#define SANGUIS_COLLISION_TEST_HPP_INCLUDED

#include <sanguis/collision/center_fwd.hpp>
#include <sanguis/collision/dim2_fwd.hpp>
#include <sanguis/creator/grid_fwd.hpp>


namespace sanguis
{
namespace collision
{

bool
test(
	sanguis::collision::center,
	sanguis::collision::dim2,
	sanguis::creator::grid const &
);

}
}

#endif
