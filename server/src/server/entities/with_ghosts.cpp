#include <sanguis/collision/world/body_enter_container.hpp>
#include <sanguis/collision/world/body_exit_container.hpp>
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
#include <fcppt/assert/optional_error.hpp>
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
	ghosts_.push_back(
		std::move(
			_ghost
		)
	);

	return
		ghosts_.back().transfer(
			FCPPT_ASSERT_OPTIONAL_ERROR(
				this->environment()
			).collision_world(),
			this->center()
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
							_ghost.transfer(
								_parameters.world(),
								_parameters.center()
							);
					}
				)
			}
		};
}

sanguis::server::entities::remove_from_world_result
sanguis::server::entities::with_ghosts::remove_from_world()
{
	sanguis::server::environment::object &cur_environment(
		FCPPT_ASSERT_OPTIONAL_ERROR(
			this->environment()
		)
	);

	return
		sanguis::server::entities::remove_from_world_result(
			fcppt::algorithm::map_concat_move<
				sanguis::collision::world::body_exit_container
			>(
				ghosts_,
				[
					this,
					&cur_environment
				](
					sanguis::server::collision::ghost &_ghost
				)
				{
					return
						_ghost.destroy(
							cur_environment.collision_world()
						);
				}
			)
		);
}

void
sanguis::server::entities::with_ghosts::update_ghost_center(
	sanguis::server::center const _center
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
