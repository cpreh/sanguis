#ifndef SANGUIS_SERVER_RANDOM_GRID_POS_AROUND_HPP_INCLUDED
#define SANGUIS_SERVER_RANDOM_GRID_POS_AROUND_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/creator/dim_fwd.hpp>
#include <sanguis/creator/optional_pos.hpp>
#include <sanguis/creator/pos_fwd.hpp>
#include <sanguis/server/random/grid_distance.hpp>

namespace sanguis::server::random
{

sanguis::creator::optional_pos grid_pos_around(
    sanguis::random_generator &, // NOLINT(google-runtime-references)
    sanguis::creator::dim const &,
    sanguis::creator::pos const &,
    sanguis::server::random::grid_distance);

}

#endif
