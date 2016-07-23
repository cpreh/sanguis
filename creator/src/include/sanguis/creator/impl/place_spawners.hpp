#ifndef SANGUIS_CREATOR_IMPL_PLACE_SPAWNERS_HPP_INCLUDED
#define SANGUIS_CREATOR_IMPL_PLACE_SPAWNERS_HPP_INCLUDED

#include <sanguis/creator/count.hpp>
#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/creator/opening_container_array_fwd.hpp>
#include <sanguis/creator/spawn_boss_fwd.hpp>
#include <sanguis/creator/spawn_container.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/creator/impl/enemy_type_container.hpp>
#include <sanguis/creator/impl/random/generator_fwd.hpp>
#include <fcppt/log/object_fwd.hpp>


namespace sanguis
{
namespace creator
{
namespace impl
{

sanguis::creator::spawn_container
place_spawners(
	fcppt::log::object &,
	sanguis::creator::grid &,
	sanguis::creator::opening_container_array const &,
	sanguis::creator::count,
	sanguis::creator::impl::random::generator &,
	sanguis::creator::impl::enemy_type_container const &,
	sanguis::creator::spawn_boss,
	// TODO use a callback instead and get rid of default parameter
	sanguis::creator::tile const =
		sanguis::creator::tile::spawner
);

}
}
}

#endif
