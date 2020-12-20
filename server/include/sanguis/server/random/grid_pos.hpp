#ifndef SANGUIS_SERVER_RANDOM_GRID_POS_HPP_INCLUDED
#define SANGUIS_SERVER_RANDOM_GRID_POS_HPP_INCLUDED

#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/creator/min_fwd.hpp>
#include <sanguis/creator/optional_pos.hpp>
#include <sanguis/creator/sup_fwd.hpp>


namespace sanguis
{
namespace server
{
namespace random
{

sanguis::creator::optional_pos
grid_pos(
	sanguis::random_generator &, // NOLINT(google-runtime-references)
	sanguis::creator::min const &,
	sanguis::creator::sup const &
);

}
}
}

#endif
