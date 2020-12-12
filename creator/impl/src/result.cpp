#include <sanguis/creator/background_grid.hpp>
#include <sanguis/creator/destructible_container.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/opening_container_array.hpp>
#include <sanguis/creator/spawn_container.hpp>
#include <sanguis/creator/impl/result.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::creator::impl::result::result(
	sanguis::creator::grid &&_grid,
	sanguis::creator::background_grid &&_background_grid,
	sanguis::creator::opening_container_array &&_openings,
	sanguis::creator::spawn_container &&_spawns,
	sanguis::creator::destructible_container &&_destructibles
)
:
	grid_(
		std::move(
			_grid
		)
	),
	background_grid_(
		std::move(
			_background_grid
		)
	),
	openings_(
		std::move(
			_openings
		)
	),
	spawns_(
		std::move(
			_spawns
		)
	),
	destructibles_(
		std::move(
			_destructibles
		)
	)
{
}

sanguis::creator::grid &
sanguis::creator::impl::result::grid()
{
	return
		grid_;
}

sanguis::creator::background_grid &
sanguis::creator::impl::result::background_grid()
{
	return
		background_grid_;
}

sanguis::creator::opening_container_array &
sanguis::creator::impl::result::openings()
{
	return
		openings_;
}

sanguis::creator::spawn_container &
sanguis::creator::impl::result::spawns()
{
	return
		spawns_;
}

sanguis::creator::destructible_container &
sanguis::creator::impl::result::destructibles()
{
	return
		destructibles_;
}
