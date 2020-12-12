#ifndef SANGUIS_CREATOR_SUP_FWD_HPP_INCLUDED
#define SANGUIS_CREATOR_SUP_FWD_HPP_INCLUDED

#include <sanguis/creator/pos.hpp>
#include <fcppt/container/grid/sup_from_pos_fwd.hpp>


namespace sanguis
{
namespace creator
{

using
sup
=
fcppt::container::grid::sup_from_pos<
	sanguis::creator::pos
>;

}
}

#endif
