#include <sanguis/creator/optional_pos.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/server/ai/pathing/optional_target.hpp>
#include <sanguis/server/ai/pathing/target.hpp>
#include <sanguis/server/ai/pathing/tile_reached.hpp>
#include <sanguis/server/ai/pathing/trail.hpp>
#include <sanguis/server/ai/pathing/update_trail.hpp>
#include <sanguis/server/entities/with_ai.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/container/maybe_back.hpp>
#include <fcppt/optional/bind.hpp>
#include <fcppt/optional/copy_value.hpp>
#include <fcppt/optional/map.hpp>


sanguis::server::ai::pathing::optional_target
sanguis::server::ai::pathing::update_trail(
	fcppt::reference<
		sanguis::server::ai::pathing::trail
	> const _trail,
	sanguis::server::entities::with_ai const &_me
)
{
	return
		fcppt::optional::map(
			fcppt::optional::bind(
				fcppt::optional::copy_value(
					fcppt::container::maybe_back(
						_trail.get()
					)
				),
				[
					&_trail,
					&_me
				](
					sanguis::creator::pos const &_next_position
				)
				{
					if(
						sanguis::server::ai::pathing::tile_reached(
							_me,
							_next_position
						)
					)
					{
						_trail.get().pop_back();

						return
							fcppt::optional::copy_value(
								fcppt::container::maybe_back(
									_trail.get()
								)
							);
					}

					return
						sanguis::creator::optional_pos(
							_next_position
						);
				}
			),
			[](
				sanguis::creator::pos const &_pos
			)
			{
				return
					sanguis::server::ai::pathing::target(
						_pos
					);
			}
		);
}
