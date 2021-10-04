#ifndef SANGUIS_CREATOR_IMPL_PLACE_OPENINGS_HPP_INCLUDED
#define SANGUIS_CREATOR_IMPL_PLACE_OPENINGS_HPP_INCLUDED

#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/creator/opening_container_array.hpp>
#include <sanguis/creator/opening_count_array_fwd.hpp>
#include <sanguis/creator/impl/random/generator_fwd.hpp>
#include <fcppt/reference_fwd.hpp>


namespace sanguis::creator::impl
{

[[nodiscard]]
sanguis::creator::opening_container_array
place_openings(
	fcppt::reference<
		sanguis::creator::grid
	>,
	sanguis::creator::impl::random::generator &, // NOLINT(google-runtime-references)
	sanguis::creator::opening_count_array
);

}

#endif
