#ifndef SANGUIS_CREATOR_IMPL_PLACE_OPENINGS_HPP_INCLUDED
#define SANGUIS_CREATOR_IMPL_PLACE_OPENINGS_HPP_INCLUDED

#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/creator/opening_container_array.hpp>
#include <sanguis/creator/opening_count_array_fwd.hpp>
#include <sanguis/creator/impl/random/generator_fwd.hpp>


namespace sanguis
{
namespace creator
{
namespace impl
{

sanguis::creator::opening_container_array
place_openings(
	sanguis::creator::grid &,
	sanguis::creator::impl::random::generator &,
	sanguis::creator::opening_count_array
);

}
}
}

#endif
