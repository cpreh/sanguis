#ifndef SANGUIS_CREATOR_AUX_RESULT_HPP_INCLUDED
#define SANGUIS_CREATOR_AUX_RESULT_HPP_INCLUDED

#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/opening_container.hpp>
#include <sanguis/creator/spawn_container.hpp>
#include <sanguis/creator/aux/result_fwd.hpp>
#include <fcppt/nonassignable.hpp>


namespace sanguis
{
namespace creator
{
namespace aux
{

class result
{
	FCPPT_NONASSIGNABLE(
		result
	);
public:
	result(
		sanguis::creator::grid const &,
		sanguis::creator::opening_container const &,
		sanguis::creator::spawn_container const &
	);

	sanguis::creator::grid const &
	grid() const;

	sanguis::creator::opening_container const &
	openings() const;

	sanguis::creator::spawn_container const &
	spawns() const;
private:
	sanguis::creator::grid const grid_;

	sanguis::creator::opening_container const openings_;

	sanguis::creator::spawn_container const spawns_;
};

}
}
}

#endif
