#ifndef SANGUIS_CREATOR_AUX__NEIGHBOR_ARRAY_FWD_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX__NEIGHBOR_ARRAY_FWD_HPP_INCLUDED

#include <sanguis/creator/pos_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <array>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace creator
{
namespace aux_
{

typedef
std::array<
	sanguis::creator::pos,
	4u
>
neighbor_array;

}
}
}

#endif
