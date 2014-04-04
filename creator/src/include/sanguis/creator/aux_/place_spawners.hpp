#ifndef SANGUIS_CREATOR_AUX__PLACE_SPAWNERS_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX__PLACE_SPAWNERS_HPP_INCLUDED

#include <sanguis/creator/count.hpp>
#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/creator/opening.hpp>
#include <sanguis/creator/spawn_container.hpp>
#include <sanguis/creator/aux_/enemy_type_container.hpp>
#include <sanguis/creator/aux_/random/generator_fwd.hpp>


namespace sanguis
{
namespace creator
{
namespace aux_
{

sanguis::creator::spawn_container
place_spawners(
	sanguis::creator::grid &,
	sanguis::creator::opening const &,
	sanguis::creator::count,
	sanguis::creator::aux_::random::generator &,
	sanguis::creator::aux_::enemy_type_container const &
);

}
}
}

#endif