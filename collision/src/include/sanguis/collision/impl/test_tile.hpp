#ifndef SANGUIS_COLLISION_IMPL_TEST_TILE_HPP_INCLUDED
#define SANGUIS_COLLISION_IMPL_TEST_TILE_HPP_INCLUDED

#include <sanguis/collision/center_fwd.hpp>
#include <sanguis/collision/duration.hpp>
#include <sanguis/collision/radius_fwd.hpp>
#include <sanguis/collision/speed_fwd.hpp>
#include <sanguis/collision/impl/optional_speed.hpp>
#include <sanguis/creator/pos_fwd.hpp>
#include <sanguis/creator/tile_fwd.hpp>


namespace sanguis
{
namespace collision
{
namespace impl
{

sanguis::collision::impl::optional_speed const
test_tile(
	sanguis::collision::center,
	sanguis::collision::radius,
	sanguis::collision::duration,
	sanguis::collision::speed,
	sanguis::creator::pos,
	sanguis::creator::tile
);

}
}
}

#endif
