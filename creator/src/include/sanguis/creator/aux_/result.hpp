#ifndef SANGUIS_CREATOR_AUX__RESULT_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX__RESULT_HPP_INCLUDED

#include <sanguis/creator/background_grid.hpp>
#include <sanguis/creator/destructible_container.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/opening_container.hpp>
#include <sanguis/creator/spawn_container.hpp>
#include <sanguis/creator/aux_/result_fwd.hpp>
#include <fcppt/nonassignable.hpp>


namespace sanguis
{
namespace creator
{
namespace aux_
{

class result
{
	FCPPT_NONASSIGNABLE(
		result
	);
public:
	result(
		sanguis::creator::grid const &,
		sanguis::creator::background_grid const &,
		sanguis::creator::opening_container const &,
		sanguis::creator::spawn_container const &,
		sanguis::creator::destructible_container const &
	);

	sanguis::creator::grid const &
	grid() const;

	sanguis::creator::background_grid const &
	background_grid() const;

	sanguis::creator::opening_container const &
	openings() const;

	sanguis::creator::spawn_container const &
	spawns() const;

	sanguis::creator::destructible_container const &
	destructibles() const;
private:
	sanguis::creator::grid const grid_;

	sanguis::creator::background_grid const background_grid_;

	sanguis::creator::opening_container const openings_;

	sanguis::creator::spawn_container const spawns_;

	sanguis::creator::destructible_container const destructibles_;
};

}
}
}

#endif
