#ifndef SANGUIS_CREATOR_IMPL_PLACE_DESTRUCTIBLES_HPP_INCLUDED
#define SANGUIS_CREATOR_IMPL_PLACE_DESTRUCTIBLES_HPP_INCLUDED

#include <sanguis/creator/destructible_container.hpp>
#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/creator/impl/random/generator_fwd.hpp>
#include <fcppt/reference_fwd.hpp>

namespace sanguis::creator::impl
{

[[nodiscard]] sanguis::creator::destructible_container place_destructibles(
    fcppt::reference<sanguis::creator::grid>,
    sanguis::creator::impl::random::generator & // NOLINT(google-runtime-references)
); // NOLINT(google-runtime-references)

}

#endif
