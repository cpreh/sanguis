#ifndef SANGUIS_CREATOR_MIN_FWD_HPP_INCLUDED
#define SANGUIS_CREATOR_MIN_FWD_HPP_INCLUDED

#include <sanguis/creator/size_type.hpp>
#include <fcppt/container/grid/min_fwd.hpp>


namespace sanguis
{
namespace creator
{

typedef
fcppt::container::grid::min<
	sanguis::creator::size_type,
	2u
>
min;

}
}

#endif
