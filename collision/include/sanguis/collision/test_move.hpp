#ifndef SANGUIS_COLLISION_TEST_MOVE_HPP_INCLUDED
#define SANGUIS_COLLISION_TEST_MOVE_HPP_INCLUDED

#include <sanguis/collision/center_fwd.hpp>
#include <sanguis/collision/duration.hpp>
#include <sanguis/collision/optional_result_fwd.hpp>
#include <sanguis/collision/radius_fwd.hpp>
#include <sanguis/collision/speed_fwd.hpp>
#include <sanguis/collision/symbol.hpp>
#include <sanguis/creator/grid_fwd.hpp>


namespace sanguis::collision
{

SANGUIS_COLLISION_SYMBOL
sanguis::collision::optional_result
test_move(
	sanguis::collision::center const &,
	sanguis::collision::radius const &,
	sanguis::collision::speed const &,
	sanguis::collision::duration,
	sanguis::creator::grid const &
);

}

#endif
