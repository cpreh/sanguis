#ifndef SANGUIS_CREATOR_POS_FWD_HPP_INCLUDED
#define SANGUIS_CREATOR_POS_FWD_HPP_INCLUDED

#include <sanguis/creator/size_type.hpp>
#include <fcppt/container/grid/dim_fwd.hpp>


namespace sanguis
{
namespace creator
{

typedef
fcppt::container::grid::dim<
	sanguis::creator::size_type,
	2u
>::type
pos;

}
}

#endif
