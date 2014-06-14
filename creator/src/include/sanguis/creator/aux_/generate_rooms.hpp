#ifndef SANGUIS_CREATOR_AUX__GENERATE_ROOMS_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX__GENERATE_ROOMS_HPP_INCLUDED

#include <sanguis/creator/dim_fwd.hpp>
#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/creator/tile_fwd.hpp>
#include <sanguis/creator/aux_/random/generator_fwd.hpp>

namespace sanguis
{
namespace creator
{
namespace aux_
{

sanguis::creator::grid
generate_rooms(
	sanguis::creator::dim,
	sanguis::creator::tile,
	sanguis::creator::tile,
	sanguis::creator::aux_::random::generator &
);

}
}
}

#endif

