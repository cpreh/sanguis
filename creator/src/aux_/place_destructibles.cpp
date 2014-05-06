#include <sanguis/creator/aux_/place_destructibles.hpp>
#include <sanguis/creator/aux_/random/generator.hpp>
#include <sanguis/creator/aux_/random/uniform_int.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/destructible.hpp>
#include <sanguis/creator/destructible_container.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/creator/tile_is_solid.hpp>
#include <fcppt/math/clamp.hpp>
#include <fcppt/container/grid/neumann_neighbors.hpp>
#include <fcppt/random/distribution/basic.hpp>
#include <fcppt/random/make_variate.hpp>

sanguis::creator::destructible_container
sanguis::creator::aux_::place_destructibles(
	sanguis::creator::grid &_grid,
	sanguis::creator::aux_::random::generator &_generator
)
{
	sanguis::creator::destructible_container
	result;

	typedef
	fcppt::random::distribution::basic<
		sanguis::creator::aux_::random::uniform_int<
			unsigned
		>
	>
	uniform_int2;

	auto roll_d8(
		fcppt::random::make_variate(
			_generator,
			uniform_int2{
				uniform_int2::param_type::min{
					1u
				},
				uniform_int2::param_type::max{
					8u
				}
			}
		)
	);

	auto place_stuff_random(
		[&]
		(unsigned _cutoff)
		-> bool
		{

			return roll_d8() <= _cutoff;
		}
	);

	auto number_of_wall_neighbors(
		[&]
		(sanguis::creator::pos const _pos)
		{
			unsigned res = 0u;

			auto neighbors(
				fcppt::container::grid::neumann_neighbors(
					_pos));
			
			for(auto &n : neighbors)
				if (
					_grid[n]
					==
					sanguis::creator::tile::concrete_wall
				)
					res++;

			return res;
		}
	);

	for(unsigned y = 0u; y < _grid.size().h(); ++y)
		for(unsigned x = 0u; x < _grid.size().w(); ++x)
		{
			sanguis::creator::pos
			const
			pos{x, y};

			if
			(
				!
				sanguis::creator::tile_is_solid(
					_grid[
						pos
					]
				)
				&&
				place_stuff_random(
					number_of_wall_neighbors(
						pos
					)
				)
			)
				result.push_back(
					sanguis::creator::destructible(
						sanguis::creator::destructible_pos(pos),
						sanguis::creator::destructible_type::barrel
					)
				);
		}

	return
		result;
}
