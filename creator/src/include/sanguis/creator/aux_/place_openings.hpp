#ifndef SANGUIS_CREATOR_AUX__PLACE_OPENINGS_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX__PLACE_OPENINGS_HPP_INCLUDED

#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/creator/opening_container.hpp>
#include <sanguis/creator/opening_count.hpp>
#include <sanguis/creator/aux_/random/uniform_size_variate_fwd.hpp>


namespace sanguis
{
namespace creator
{
namespace aux_
{

sanguis::creator::opening_container
place_openings(
	sanguis::creator::grid &,
	sanguis::creator::opening_count,
	sanguis::creator::aux_::random::uniform_size_variate &,
	sanguis::creator::aux_::random::uniform_size_variate &
);

}
}
}

#endif
