#ifndef SANGUIS_CREATOR_AUX__FIND_OPPOSING_CELL_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX__FIND_OPPOSING_CELL_HPP_INCLUDED

#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/creator/pos_fwd.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace creator
{
namespace aux_
{

fcppt::optional<
	sanguis::creator::pos
>
find_opposing_cell(
	sanguis::creator::grid &,
	std::vector<
		sanguis::creator::pos
	> &,
	sanguis::creator::pos const &
);

}
}
}

#endif
