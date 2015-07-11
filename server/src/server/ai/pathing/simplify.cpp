#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/creator/optional_pos.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/server/ai/pathing/can_walk_diagonally.hpp>
#include <sanguis/server/ai/pathing/simplify.hpp>
#include <sanguis/server/ai/pathing/trail.hpp>
#include <fcppt/make_int_range_count.hpp>
#include <fcppt/maybe.hpp>
#include <fcppt/maybe_multi.hpp>
#include <fcppt/algorithm/join.hpp>
#include <fcppt/algorithm/map_optional.hpp>
#include <fcppt/container/at_optional.hpp>
#include <fcppt/container/maybe_front.hpp>


sanguis::server::ai::pathing::trail
sanguis::server::ai::pathing::simplify(
	sanguis::server::ai::pathing::trail const &_trail,
	sanguis::creator::grid const &_grid
)
{
	return
		fcppt::maybe(
			fcppt::container::maybe_front(
				_trail
			),
			[]{
				return
					sanguis::server::ai::pathing::trail();
			},
			[
				&_grid,
				&_trail
			](
				sanguis::creator::pos const _start
			)
			{
				return
					fcppt::algorithm::join(
						sanguis::server::ai::pathing::trail{
							_start
						},
						fcppt::algorithm::map_optional<
							sanguis::server::ai::pathing::trail
						>(
							fcppt::make_int_range_count(
								_trail.size()
								-
								1u
							),
							[
								&_grid,
								&_trail
							](
								sanguis::server::ai::pathing::trail::size_type const _index
							)
							{
								sanguis::creator::optional_pos const next1(
									fcppt::container::at_optional(
										_trail,
										_index
										+
										1u
									)
								);

								sanguis::creator::optional_pos const next2(
									fcppt::container::at_optional(
										_trail,
										_index
										+
										2u
									)
								);

								return
									fcppt::maybe_multi(
										[]{
											// In this case, next1 is set to the node the entity is on.
											return
												sanguis::creator::optional_pos();
										},
										[
											_index,
											&_grid,
											&_trail
										](
											sanguis::creator::pos const _next1,
											sanguis::creator::pos const _next2
										)
										{
											return
												sanguis::server::ai::pathing::can_walk_diagonally(
													_grid,
													_trail[
														_index
													],
													_next1,
													_next2
												)
												?
													sanguis::creator::optional_pos(
														_next1
													)
												:
													sanguis::creator::optional_pos()
												;
										},
										next1,
										next2
									);
							}
						)
					);
				}
		);
}
