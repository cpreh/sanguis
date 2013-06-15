#ifndef SANGUIS_CREATOR_POS_FWD_HPP_INCLUDED
#define SANGUIS_CREATOR_POS_FWD_HPP_INCLUDED

#include <sanguis/creator/size_type.hpp>
#include <fcppt/container/grid/pos_fwd.hpp>


namespace sanguis
{
namespace creator
{

typedef
fcppt::container::grid::pos<
	sanguis::creator::size_type,
	2u
> pos;

}
}

#endif
