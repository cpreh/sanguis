#include <sanguis/is_primary_weapon.hpp>
#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/server/ai/rotate_and_move_to_target.hpp>
#include <sanguis/server/ai/simple.hpp>
#include <sanguis/server/ai/idle.hpp>
#include <sanguis/server/ai/sight_range.hpp>
#include <sanguis/server/ai/pathing/find_target.hpp>
#include <sanguis/server/ai/pathing/is_visible.hpp>
#include <sanguis/server/ai/pathing/positions_are_close.hpp>
#include <sanguis/server/ai/pathing/start.hpp>
#include <sanguis/server/ai/pathing/target.hpp>
#include <sanguis/server/ai/pathing/trail.hpp>
#include <sanguis/server/entities/with_ai.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/with_links.hpp>
#include <sanguis/server/weapons/target.hpp>
#include <sanguis/server/world/center_to_grid_pos.hpp>
#include <sanguis/server/world/grid_pos_to_center.hpp>


sanguis::server::ai::simple::simple(
	sanguis::server::entities::with_ai &_me,
	sanguis::server::ai::sight_range const _sight_range
)
:
	me_(
		_me
	),
	sight_range_(
		_sight_range
	),
	target_(),
	trail_()
{
}

sanguis::server::ai::simple::~simple()
{
}

void
sanguis::server::ai::simple::in_range(
	sanguis::server::entities::with_body &_entity
)
{
	if(
		!target_
	)
		this->new_target(
			_entity
		);
}

void
sanguis::server::ai::simple::distance_changes(
	sanguis::server::entities::with_body &_entity
)
{
	// TODO: When do we pick up a new target?
	if(
		!target_
	)
		this->new_target(
			_entity
		);
}

void
sanguis::server::ai::simple::update(
	sanguis::creator::grid const &_grid
)
{
	if(
		!target_
	)
	{
		sanguis::server::ai::idle(
			me_
		);

		return;
	}

	sanguis::creator::pos const target_grid_pos(
		sanguis::server::world::center_to_grid_pos(
			target_->center()
		)
	);

	sanguis::creator::pos const my_grid_pos(
		sanguis::server::world::center_to_grid_pos(
			me_.center()
		)
	);

	if(
		sanguis::server::ai::pathing::is_visible(
			_grid,
			target_grid_pos,
			my_grid_pos
		)
	)
	{
		me_.target(
			sanguis::server::weapons::target(
				target_->center().get()
			)
		);

		me_.use_weapon(
			true,
			sanguis::is_primary_weapon(
				true
			)
		);
	}

	if(
		sanguis::server::ai::pathing::positions_are_close(
			target_grid_pos,
			my_grid_pos
		)
	)
	{
		sanguis::server::ai::rotate_and_move_to_target(
			me_,
			target_->center()
		);

		return;
	}

	if(
		trail_.empty()
		||
		!sanguis::server::ai::pathing::positions_are_close(
			trail_.front(),
			target_grid_pos
		)
	)
		trail_ =
			sanguis::server::ai::pathing::find_target(
				_grid,
				sanguis::server::ai::pathing::start(
					my_grid_pos
				),
				sanguis::server::ai::pathing::target(
					target_grid_pos
				)
			);

	if(
		trail_.empty()
	)
	{
		sanguis::server::ai::idle(
			me_
		);

		return;
	}

	sanguis::creator::pos const next_position(
		trail_.back()
	);

	sanguis::server::ai::rotate_and_move_to_target(
		me_,
		sanguis::server::world::grid_pos_to_center(
			next_position
		)
	);

	if(
		sanguis::server::ai::pathing::positions_are_close(
			my_grid_pos,
			next_position
		)
	)
		trail_.pop_back();
}

sanguis::server::ai::sight_range const
sanguis::server::ai::simple::sight_range() const
{
	return
		sight_range_;
}

void
sanguis::server::ai::simple::new_target(
	sanguis::server::entities::with_body &_with_body
)
{
	target_ = _with_body.link();

	trail_.clear();
}
