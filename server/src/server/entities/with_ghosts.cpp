#include <sanguis/collision/world/body_enter_container.hpp>
#include <sanguis/collision/world/body_exit_container.hpp>
#include <sanguis/collision/world/object_fwd.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/collision/ghost.hpp>
#include <sanguis/server/collision/ghost_container.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/optional_transfer_result.hpp>
#include <sanguis/server/entities/remove_from_world_result.hpp>
#include <sanguis/server/entities/transfer_parameters.hpp>
#include <sanguis/server/entities/transfer_result.hpp>
#include <sanguis/server/entities/with_ghosts.hpp>
#include <sanguis/server/environment/object.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/map_concat_move.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::with_ghosts::with_ghosts()
:
	sanguis::server::entities::base(),
	ghosts_()
{
}

sanguis::server::entities::with_ghosts::with_ghosts(
	sanguis::server::collision::ghost_container &&_ghosts
)
:
	sanguis::server::entities::base(),
	ghosts_(
		std::move(
			_ghosts
		)
	)
{
}

sanguis::server::entities::with_ghosts::~with_ghosts()
{
}

sanguis::collision::world::body_enter_container
sanguis::server::entities::with_ghosts::add_ghost(
	sanguis::server::collision::ghost &&_ghost
)
{
	FCPPT_ASSERT_PRE(
		this->environment()
	);

	ghosts_.push_back(
		std::move(
			_ghost
		)
	);

	return
		this->transfer_ghost(
			ghosts_.back(),
			this->environment()->collision_world()
		);
}

void
sanguis::server::entities::with_ghosts::init_ghosts(
	sanguis::server::collision::ghost_container &&_ghosts
)
{
	FCPPT_ASSERT_PRE(
		ghosts_.empty()
	);

	ghosts_ =
		std::move(
			_ghosts
		);
}

sanguis::server::entities::optional_transfer_result
sanguis::server::entities::with_ghosts::on_transfer(
	sanguis::server::entities::transfer_parameters const &_parameters
)
{
	return
		sanguis::server::entities::optional_transfer_result{
			sanguis::server::entities::transfer_result{
				fcppt::algorithm::map_concat_move<
					sanguis::collision::world::body_enter_container
				>(
					ghosts_,
					[
						&_parameters,
						this
					](
						sanguis::server::collision::ghost &_ghost
					)
					{
						return
							this->transfer_ghost(
								_ghost,
								_parameters.world()
							);
					}
				)
			}
		};
}

sanguis::server::entities::remove_from_world_result
sanguis::server::entities::with_ghosts::remove_from_world()
{
	return
		sanguis::server::entities::remove_from_world_result(
			fcppt::algorithm::map_concat_move<
				sanguis::collision::world::body_exit_container
			>(
				ghosts_,
				[
					this
				](
					sanguis::server::collision::ghost &_ghost
				)
				{
					return
						_ghost.destroy(
							this->environment()->collision_world()
						);
				}
			)
		);
}

void
sanguis::server::entities::with_ghosts::update_center(
	sanguis::server::center const &_center
)
{
	for(
		auto &ghost
		:
		ghosts_
	)
		ghost.center(
			_center
		);
}

sanguis::collision::world::body_enter_container
sanguis::server::entities::with_ghosts::transfer_ghost(
	sanguis::server::collision::ghost &_ghost,
	sanguis::collision::world::object &_world
)
{
	return
		_ghost.transfer(
			_world,
			this->center()
		);
}
