#ifndef SANGUIS_COLLISION_TEST_MOVE_HPP_INCLUDED
#define SANGUIS_COLLISION_TEST_MOVE_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/collision/center_fwd.hpp>
#include <sanguis/collision/dim2_fwd.hpp>
#include <sanguis/collision/optional_result_fwd.hpp>
#include <sanguis/collision/speed_fwd.hpp>
#include <sanguis/creator/grid_fwd.hpp>


namespace sanguis
{
namespace collision
{

sanguis::collision::optional_result const
test_move(
	sanguis::collision::center,
	sanguis::collision::dim2,
	sanguis::collision::speed,
	sanguis::duration,
	sanguis::creator::grid const &
);

}
}

#endif
