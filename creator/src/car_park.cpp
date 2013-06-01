#include <sanguis/creator/car_park.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/name.hpp>
#include <sanguis/creator/parameters.hpp>
#include <sanguis/creator/result.hpp>
#include <sanguis/creator/seed.hpp>
#include <sanguis/creator/tile.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/remove.hpp>
#include <fcppt/algorithm/contains.hpp>
#include <fcppt/algorithm/append.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/optional.hpp>
#include <fcppt/math/dim/output.hpp>
#include <sanguis/creator/randgen.hpp>
#include <fcppt/container/grid/make_pos_range.hpp>
#include <fcppt/assign/make_container.hpp>
#include <fcppt/random/distribution/basic.hpp>
#include <fcppt/random/distribution/parameters/uniform_real.hpp>
#include <fcppt/random/distribution/parameters/uniform_int.hpp>

namespace
{
std::vector<
	sanguis::creator::grid::dim
>
neighbors(
	sanguis::creator::grid::dim const &
);

fcppt::optional<
	sanguis::creator::grid::dim
>
find_opposing_cell(
	sanguis::creator::grid &,
	std::vector<
		sanguis::creator::grid::dim
	> &,
	sanguis::creator::grid::dim const &
);

void add_neighbors_to_walls(
	sanguis::creator::grid &,
	sanguis::creator::grid::dim const &,
	std::vector<
		sanguis::creator::grid::dim
	> &
);
}

sanguis::creator::result
sanguis::creator::car_park(
	sanguis::creator::parameters const &_parameters
)
{
	typedef fcppt::random::distribution::basic<
		fcppt::random::distribution::parameters::uniform_real<
			double
		>
	> uniform_real;

	typedef fcppt::random::distribution::basic<
		fcppt::random::distribution::parameters::uniform_int<
			std::size_t
		>
	> uniform_int;

	uniform_real distribution(
		uniform_real::param_type::min(
			0.0
		),
		uniform_real::param_type::sup(
			1.0
		)
	);

	sanguis::creator::grid ret(
		sanguis::creator::grid::dim(
			31,
			31
			/*
			_parameters.size().w(),
			_parameters.size().h()
			*/
		),
		sanguis::creator::tile::concrete_wall
	);

	uniform_int int_distribution(
		uniform_int::param_type::min(
			0u
		),
		uniform_int::param_type::max(
				ret.size().w() *
				ret.size().h()
		)
	);

	//TODO: choose random starting pos
	sanguis::creator::grid::dim starting_pos(
		5,
		5
	);

	// add entry and exit
	// TODO: randomize these also
	ret[
		sanguis::creator::grid::dim(
			1,
			0
		)] =
		sanguis::creator::tile::nothing;

	ret[
		sanguis::creator::grid::dim(
			ret.size().w() - 1,
			ret.size().h() - 2
		)] =
		sanguis::creator::tile::nothing;

	for (
		auto const cell :
		fcppt::container::grid::make_pos_range(
			ret)
	)
	{
		if (
			cell.pos().w() % 2 == 1
			&&
			cell.pos().h() % 2 == 1
		)
			cell.value() =
				sanguis::creator::tile::nothing;
	}

	std::vector<
		sanguis::creator::grid::dim
	> walls;

	std::vector<
		sanguis::creator::grid::dim
	> maze;

	::add_neighbors_to_walls(
		ret,
		starting_pos,
		walls
	);

	while (!walls.empty())
	{
		sanguis::creator::grid::dim const
		random_wall =
			walls[
				int_distribution(
					_parameters.randgen()
				) %
				walls.size()
			];

		fcppt::optional<
			sanguis::creator::grid::dim
		>
		opposing_cell =
			find_opposing_cell(
				ret,
				maze,
				random_wall);

		if(
			opposing_cell
		)
		{
			ret[
				random_wall
			] =
				sanguis::creator::tile::nothing;

			ret[
				*opposing_cell
			] =
				sanguis::creator::tile::nothing;

			maze.push_back(
				*opposing_cell
			);

			fcppt::algorithm::append(
				walls,
				::neighbors(
					*opposing_cell
				)
			);
		}
		fcppt::algorithm::remove(
			walls,
			random_wall
		);
	}

	return
		sanguis::creator::result(
			ret,
			sanguis::creator::seed(
				0u
			),
			sanguis::creator::name(
				FCPPT_TEXT("car_park")
			)
		);
}

namespace
{

fcppt::optional<
	sanguis::creator::grid::dim
>
find_opposing_cell
(
	sanguis::creator::grid &grid,
	std::vector<
		sanguis::creator::grid::dim
	> &maze,
	sanguis::creator::grid::dim const &cell
)
{

	if (cell.w() == grid.size().w() - 1
		||
		cell.w() == 0
		||
		cell.h() == grid.size().h() - 1
		||
		cell.h() == 0
		)
		return fcppt::optional<
			sanguis::creator::grid::dim
		>();

	std::vector<
		sanguis::creator::grid::dim
	>
	candidates;

	std::vector<
		sanguis::creator::grid::dim
	>
	neighbors =
		::neighbors(
				cell
		);

	std::copy_if(
		neighbors.begin(),
		neighbors.end(),
		std::back_inserter(candidates),
		[&grid](
			sanguis::creator::grid::dim &elem
		)
		{
			return
				grid[elem] 
					==
				sanguis::creator::tile::nothing;
		}
	);

	// this should never happen, if the algorithm is correct
	FCPPT_ASSERT_ERROR(
		candidates.size() == 2);
	if(!fcppt::algorithm::contains(maze, candidates[0]))
		return fcppt::optional<
			sanguis::creator::grid::dim
		>(candidates[0]);
	if(!fcppt::algorithm::contains(maze, candidates[1]))
		return fcppt::optional<
			sanguis::creator::grid::dim
		>(candidates[1]);
	return fcppt::optional<
		sanguis::creator::grid::dim
	>();
}

// returns the von-Neumann-neighbors of the given cell
// no range checks are being made!
std::vector<
	sanguis::creator::grid::dim
>
neighbors(
	sanguis::creator::grid::dim const &cell
)
{
	std::vector<sanguis::creator::grid::dim> ret{
			sanguis::creator::grid::dim{
				cell.w() - 1,
				cell.h()
			},
			sanguis::creator::grid::dim{
				cell.w() + 1,
				cell.h()
			},
			sanguis::creator::grid::dim{
				cell.w(),
				cell.h() - 1,
			},
			sanguis::creator::grid::dim{
				cell.w(),
				cell.h() + 1
			}
		};

	return ret;
}


void add_neighbors_to_walls(
	sanguis::creator::grid &grid,
	sanguis::creator::grid::dim const &starting_pos,
	std::vector<
		sanguis::creator::grid::dim
	> &walls
)
{

	for (
		auto &pos :
		::neighbors(
			starting_pos)
	)
	{
		if (
			grid[
				pos]
			== sanguis::creator::tile::concrete_wall
		)
		{
			walls.push_back(
				pos
			);
		}
	}
}
}
