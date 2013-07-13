#ifndef SANGUIS_CREATOR_AUX_NEUMANN_NEIGHBORS_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX_NEUMANN_NEIGHBORS_HPP_INCLUDED

#include <sanguis/creator/pos_fwd.hpp>
#include <sanguis/creator/aux/neighbor_array_fwd.hpp>


namespace sanguis
{
namespace creator
{
namespace aux
{

sanguis::creator::aux::neighbor_array const
neumann_neighbors(
	sanguis::creator::pos
);

}
}
}

#endif
