#ifndef SANGUIS_CREATOR_AUX__CLOSEST_EMPTY_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX__CLOSEST_EMPTY_HPP_INCLUDED

#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/creator/pos_fwd.hpp>
#include <sanguis/creator/aux_/optional_pos.hpp>


namespace sanguis
{
namespace creator
{
namespace aux_
{

sanguis::creator::aux_::optional_pos const
closest_empty(
	sanguis::creator::grid const &,
	sanguis::creator::pos
);

}
}
}

#endif
