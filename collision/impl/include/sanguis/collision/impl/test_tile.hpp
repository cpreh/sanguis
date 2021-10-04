#ifndef SANGUIS_COLLISION_IMPL_TEST_TILE_HPP_INCLUDED
#define SANGUIS_COLLISION_IMPL_TEST_TILE_HPP_INCLUDED

#include <sanguis/collision/center_fwd.hpp>
#include <sanguis/collision/duration.hpp>
#include <sanguis/collision/radius_fwd.hpp>
#include <sanguis/collision/speed_fwd.hpp>
#include <sanguis/collision/impl/optional_speed.hpp>
#include <sanguis/creator/pos_fwd.hpp>
#include <sanguis/creator/tile_fwd.hpp>


namespace sanguis::collision::impl
{

sanguis::collision::impl::optional_speed
test_tile(
	sanguis::collision::center const &,
	sanguis::collision::radius const &,
	sanguis::collision::duration,
	sanguis::collision::speed const &,
	sanguis::creator::pos const &,
	sanguis::creator::tile
);

}

#endif
