#include <sanguis/creator/exception.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/opening.hpp>
#include <sanguis/creator/opening_container_array.hpp>
#include <sanguis/creator/opening_count.hpp>
#include <sanguis/creator/opening_count_array.hpp>
#include <sanguis/creator/opening_type.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/aux_/closest_empty.hpp>
#include <sanguis/creator/aux_/place_openings.hpp>
#include <sanguis/creator/aux_/set_opening_tiles.hpp>
#include <sanguis/creator/aux_/random/uniform_pos.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/make_literal_strong_typedef.hpp>
#include <fcppt/maybe.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/enum_array_fold.hpp>
#include <fcppt/algorithm/map.hpp>


sanguis::creator::opening_container_array
sanguis::creator::aux_::place_openings(
	sanguis::creator::grid &_grid,
	sanguis::creator::aux_::random::generator &_generator,
	sanguis::creator::opening_count_array const _opening_count_array
)
{
	sanguis::creator::aux_::random::uniform_pos
	random_pos{
		_generator,
		_grid.size()
	};

	auto const result(
		fcppt::algorithm::enum_array_fold<
			sanguis::creator::opening_container_array
		>(
			[
				&random_pos,
				&_grid,
				&_opening_count_array
			](
				sanguis::creator::opening_type const _opening
			)
			{
				return
					fcppt::algorithm::map<
						sanguis::creator::opening_container
					>(
						fcppt::make_int_range_count(
							_opening_count_array[
								_opening
							]
						),
						[
							&random_pos,
							&_grid
						](
							sanguis::creator::opening_count
						)
						{
							return
								fcppt::maybe(
									sanguis::creator::aux_::closest_empty(
										_grid,
										random_pos()
									),
									[]()
									->
									sanguis::creator::opening
									{
										throw
											sanguis::creator::exception{
												FCPPT_TEXT("Unable to find a free tile for an opening.")
											};
									},
									[](
										sanguis::creator::pos const _pos
									)
									{
										return
											sanguis::creator::opening{
												_pos
											};
									}
								);
						}
					);
			}
		)
	);

	sanguis::creator::aux_::set_opening_tiles(
		_grid,
		result
	);

	return
		result;
}
