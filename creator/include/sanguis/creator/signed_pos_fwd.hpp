#ifndef SANGUIS_CREATOR_SIGNED_POS_FWD_HPP_INCLUDED
#define SANGUIS_CREATOR_SIGNED_POS_FWD_HPP_INCLUDED

#include <sanguis/creator/difference_type.hpp>
#include <fcppt/container/grid/pos_fwd.hpp>


namespace sanguis::creator
{

using
signed_pos
=
fcppt::container::grid::pos<
	sanguis::creator::difference_type,
	2
>;

}

#endif
