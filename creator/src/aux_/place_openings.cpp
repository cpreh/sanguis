#include <sanguis/creator/exception.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/opening.hpp>
#include <sanguis/creator/opening_container.hpp>
#include <sanguis/creator/opening_count.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/tile.hpp>
#include <sanguis/creator/aux_/closest_empty.hpp>
#include <sanguis/creator/aux_/place_openings.hpp>
#include <sanguis/creator/aux_/optional_pos.hpp>
#include <sanguis/creator/aux_/random/uniform_size_variate.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/contains.hpp>
#include <fcppt/assert/error_message.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/vector/comparison.hpp>
#include <fcppt/math/vector/dim.hpp>


sanguis::creator::opening_container
sanguis::creator::aux_::place_openings(
	sanguis::creator::grid &_grid,
	sanguis::creator::opening_count const _opening_count,
	sanguis::creator::aux_::random::uniform_size_variate &_random_x,
	sanguis::creator::aux_::random::uniform_size_variate &_random_y
)
{
	sanguis::creator::aux_::optional_pos const opt_starting_pos{
		sanguis::creator::aux_::closest_empty(
			_grid,
			sanguis::creator::pos(
				_random_x(),
				_random_y()
			)
		)
	};

	if(
		!opt_starting_pos
	)
		throw
			sanguis::creator::exception{
				FCPPT_TEXT("Couldn't find a starting position to place openings!")
			};

	sanguis::creator::pos const starting_pos{
		*opt_starting_pos
	};

	sanguis::creator::opening_container
	result{
		1u,
		sanguis::creator::opening(
			starting_pos
		)
	};

	sanguis::creator::aux_::optional_pos const
	possible_opening{
		sanguis::creator::aux_::closest_empty(
			_grid,
			(starting_pos + _grid.size() / 2u) % _grid.size()
		)
	};

	FCPPT_ASSERT_ERROR_MESSAGE(
		possible_opening.has_value(),
		FCPPT_TEXT(
			"Could not find a free tile close enough to the exit!"
		)
	);

	result.push_back(
		sanguis::creator::opening{
			*possible_opening
		}
	);

	// all remaining result
	sanguis::creator::opening_container::size_type
	current_results{
		result.size()
	};

	sanguis::creator::opening_count::value_type iterations{
		0u
	};

	while(
		current_results
		<
		_opening_count.get()
	)
	{
		if(
			++iterations
			>
			_opening_count.get() * 5
		)
			throw sanguis::creator::exception(
				FCPPT_TEXT(
					"Could not place opening, giving up."
				)
			);

		sanguis::creator::aux_::optional_pos const
		candidate{
			sanguis::creator::aux_::closest_empty(
				_grid,
				sanguis::creator::grid::pos{
					_random_x(),
					_random_y()
				}
			)
		};

		if(
			!candidate
		)
			continue;

		sanguis::creator::opening const
		next_opening{
			sanguis::creator::opening(
				*candidate
			)
		};

		if(
			!fcppt::algorithm::contains(
				result,
				next_opening
			)
		)
		{
			result.push_back(
				next_opening
			);

			++current_results;
		}
	}

	for(
		auto const &opening
		:
		result
	)
		_grid
		[
			opening.get()
		] =
			sanguis::creator::tile::door;

	return
		result;
}
