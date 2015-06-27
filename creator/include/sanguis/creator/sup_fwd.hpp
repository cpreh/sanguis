#ifndef SANGUIS_CREATOR_SUP_FWD_HPP_INCLUDED
#define SANGUIS_CREATOR_SUP_FWD_HPP_INCLUDED

#include <sanguis/creator/size_type.hpp>
#include <fcppt/container/grid/sup_fwd.hpp>


namespace sanguis
{
namespace creator
{

typedef
fcppt::container::grid::sup<
	sanguis::creator::size_type,
	2u
>
sup;

}
}

#endif
