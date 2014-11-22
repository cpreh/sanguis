#include <sanguis/creator/pos.hpp>
#include <sanguis/server/ai/context.hpp>
#include <sanguis/server/ai/pathing/can_walk_diagonally.hpp>
#include <sanguis/server/ai/pathing/find_target.hpp>
#include <sanguis/server/ai/pathing/optional_target.hpp>
#include <sanguis/server/ai/pathing/start.hpp>
#include <sanguis/server/ai/pathing/target.hpp>
#include <sanguis/server/ai/pathing/trail.hpp>
#include <sanguis/server/entities/with_ai.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/world/center_to_grid_pos.hpp>


sanguis::server::ai::context::context(
	sanguis::server::entities::with_ai &_me
)
:
	me_(
		_me
	),
	trail_()
{
}

sanguis::server::ai::context::~context()
{
}

bool
sanguis::server::ai::context::path_find(
	sanguis::creator::pos const _pos
)
{
	trail_ =
		sanguis::server::ai::pathing::find_target(
			this->grid(),
			sanguis::server::ai::pathing::start(
				sanguis::server::world::center_to_grid_pos(
					me_.center()
				)
			),
			sanguis::server::ai::pathing::target(
				_pos
			)
		);

	return
		!trail_.empty();
}

void
sanguis::server::ai::context::clear_path()
{
	trail_.clear();
}

sanguis::server::ai::pathing::optional_target const
sanguis::server::ai::context::continue_path()
{
	if(
		trail_.empty()
	)
		return
			sanguis::server::ai::pathing::optional_target();

	sanguis::creator::pos const next_position(
		trail_.back()
	);

	// TODO: Return the next position after pop_back
	if(
		sanguis::server::ai::pathing::can_walk_diagonally(
			this->grid(),
			sanguis::server::world::center_to_grid_pos(
				me_.center()
			),
			next_position
		)
	)
		trail_.pop_back();

	return
		sanguis::server::ai::pathing::optional_target{
			sanguis::server::ai::pathing::target(
				next_position
			)
		};
}

sanguis::creator::grid const &
sanguis::server::ai::context::grid() const
{
	return
		this->me().environment()->grid();
}

sanguis::server::entities::with_ai &
sanguis::server::ai::context::me()
{
	return
		me_;
}

sanguis::server::entities::with_ai const &
sanguis::server::ai::context::me() const
{
	return
		me_;
}
