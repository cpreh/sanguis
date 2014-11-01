#ifndef SANGUIS_CREATOR_AUX__PLACE_SPAWNERS_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX__PLACE_SPAWNERS_HPP_INCLUDED

#include <sanguis/creator/count.hpp>
#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/creator/opening_container_array_fwd.hpp>
#include <sanguis/creator/spawn_boss_fwd.hpp>
#include <sanguis/creator/spawn_container.hpp>
#include <sanguis/creator/tile.hpp>
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
	sanguis::creator::opening_container_array const &,
	sanguis::creator::count,
	sanguis::creator::aux_::random::generator &,
	sanguis::creator::aux_::enemy_type_container const &,
	sanguis::creator::spawn_boss,
	// TODO use a callback instead and get rid of default parameter
	sanguis::creator::tile const =
		sanguis::creator::tile::spawner
);

}
}
}

#endif
