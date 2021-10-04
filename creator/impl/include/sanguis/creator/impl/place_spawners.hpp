#ifndef SANGUIS_CREATOR_IMPL_PLACE_SPAWNERS_HPP_INCLUDED
#define SANGUIS_CREATOR_IMPL_PLACE_SPAWNERS_HPP_INCLUDED

#include <sanguis/creator/count.hpp>
#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/creator/opening_container_array_fwd.hpp>
#include <sanguis/creator/spawn_boss_fwd.hpp>
#include <sanguis/creator/spawn_container.hpp>
#include <sanguis/creator/tile_fwd.hpp>
#include <sanguis/creator/impl/enemy_type_container.hpp>
#include <sanguis/creator/impl/random/generator_fwd.hpp>
#include <fcppt/reference_fwd.hpp>
#include <fcppt/log/object_fwd.hpp>


namespace sanguis::creator::impl
{

[[nodiscard]]
sanguis::creator::spawn_container
place_spawners(
	fcppt::log::object &, // NOLINT(google-runtime-references)
	fcppt::reference<
		sanguis::creator::grid
	>,
	sanguis::creator::opening_container_array const &,
	sanguis::creator::count,
	sanguis::creator::impl::random::generator &, // NOLINT(google-runtime-references)
	sanguis::creator::impl::enemy_type_container const &,
	sanguis::creator::spawn_boss,
	sanguis::creator::tile // sanguis::creator::tile::spawner
);

}

#endif
