#ifndef SANGUIS_CREATOR_AUX__PLACE_DESTRUCTIBLES_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX__PLACE_DESTRUCTIBLES_HPP_INCLUDED

#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/creator/destructible_container.hpp>
#include <sanguis/creator/aux_/random/generator_fwd.hpp>


namespace sanguis
{
namespace creator
{
namespace aux_
{

sanguis::creator::destructible_container
place_destructibles(
	sanguis::creator::grid &,
	sanguis::creator::aux_::random::generator &
);

}
}
}

#endif
