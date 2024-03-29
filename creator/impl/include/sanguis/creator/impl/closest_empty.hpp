#ifndef SANGUIS_CREATOR_IMPL_CLOSEST_EMPTY_HPP_INCLUDED
#define SANGUIS_CREATOR_IMPL_CLOSEST_EMPTY_HPP_INCLUDED

#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/creator/pos_fwd.hpp>
#include <sanguis/creator/impl/optional_pos.hpp>

namespace sanguis::creator::impl
{

sanguis::creator::impl::optional_pos
closest_empty(sanguis::creator::grid const &, sanguis::creator::pos const &);

}

#endif
