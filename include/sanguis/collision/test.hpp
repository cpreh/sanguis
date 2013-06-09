#ifndef SANGUIS_COLLISION_TEST_HPP_INCLUDED
#define SANGUIS_COLLISION_TEST_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/collision/center_fwd.hpp>
#include <sanguis/collision/optional_result_fwd.hpp>
#include <sanguis/collision/radius_fwd.hpp>
#include <sanguis/collision/speed_fwd.hpp>
#include <sanguis/creator/grid_fwd.hpp>


namespace sanguis
{
namespace collision
{

sanguis::collision::optional_result const
test(
	sanguis::collision::center,
	sanguis::collision::radius,
	sanguis::collision::speed,
	sanguis::duration,
	sanguis::creator::grid const &
);

}
}

#endif
