#include <sanguis/creator/exception.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/opening.hpp>
#include <sanguis/creator/opening_container_array.hpp>
#include <sanguis/creator/opening_count.hpp>
#include <sanguis/creator/opening_count_array.hpp>
#include <sanguis/creator/opening_type.hpp>
#include <sanguis/creator/impl/closest_empty.hpp>
#include <sanguis/creator/impl/place_openings.hpp>
#include <sanguis/creator/impl/set_opening_tiles.hpp>
#include <sanguis/creator/impl/random/uniform_pos.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/make_literal_strong_typedef.hpp>
#include <fcppt/optional_to_exception.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/enum_array_fold.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/type_iso/strong_typedef.hpp>


sanguis::creator::opening_container_array
sanguis::creator::impl::place_openings(
	sanguis::creator::grid &_grid,
	sanguis::creator::impl::random::generator &_generator,
	sanguis::creator::opening_count_array const _opening_count_array
)
{
	sanguis::creator::impl::random::uniform_pos
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
								sanguis::creator::opening{
									fcppt::optional_to_exception(
										sanguis::creator::impl::closest_empty(
											_grid,
											random_pos()
										),
										[]{
											return
												sanguis::creator::exception{
													FCPPT_TEXT("Unable to find a free tile for an opening.")
												};
										}
									)
								};
						}
					);
			}
		)
	);

	sanguis::creator::impl::set_opening_tiles(
		_grid,
		result
	);

	return
		result;
}
