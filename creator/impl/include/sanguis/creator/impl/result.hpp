#ifndef SANGUIS_CREATOR_IMPL_RESULT_HPP_INCLUDED
#define SANGUIS_CREATOR_IMPL_RESULT_HPP_INCLUDED

#include <sanguis/creator/background_grid.hpp>
#include <sanguis/creator/destructible_container.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/opening_container_array.hpp>
#include <sanguis/creator/spawn_container.hpp>
#include <sanguis/creator/impl/result_fwd.hpp>


namespace sanguis::creator::impl
{

class result
{
public:
	result(
		sanguis::creator::grid &&,
		sanguis::creator::background_grid &&,
		sanguis::creator::opening_container_array &&,
		sanguis::creator::spawn_container &&,
		sanguis::creator::destructible_container &&
	);

	[[nodiscard]]
	sanguis::creator::grid &
	grid();

	[[nodiscard]]
	sanguis::creator::background_grid &
	background_grid();

	[[nodiscard]]
	sanguis::creator::opening_container_array &
	openings();

	[[nodiscard]]
	sanguis::creator::spawn_container &
	spawns();

	[[nodiscard]]
	sanguis::creator::destructible_container &
	destructibles();
private:
	sanguis::creator::grid grid_;

	sanguis::creator::background_grid background_grid_;

	sanguis::creator::opening_container_array openings_;

	sanguis::creator::spawn_container spawns_;

	sanguis::creator::destructible_container destructibles_;
};

}

#endif
