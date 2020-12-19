#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/ai/context.hpp>
#include <sanguis/server/ai/context_ref.hpp>
#include <sanguis/server/ai/go_to_grid_pos.hpp>
#include <sanguis/server/ai/make_path.hpp>
#include <sanguis/server/ai/speed_factor.hpp>
#include <sanguis/server/ai/status.hpp>
#include <sanguis/server/ai/behavior/base.hpp>
#include <sanguis/server/ai/behavior/stay.hpp>
#include <sanguis/server/collision/distance_pos_pos.hpp>
#include <sanguis/server/entities/with_ai.hpp>
#include <sanguis/server/world/center_to_grid_pos.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_literal_strong_typedef.hpp>


sanguis::server::ai::behavior::stay::stay(
	sanguis::server::ai::context_ref const _context
)
:
	sanguis::server::ai::behavior::base(
		_context
	),
	start_pos_{
		_context->me().center()
	}
{
}

sanguis::server::ai::behavior::stay::~stay()
= default;

bool
sanguis::server::ai::behavior::stay::start()
{
	return
		sanguis::server::collision::distance_pos_pos(
			start_pos_.get(),
			this->me().center().get()
		)
		>=
		fcppt::literal<
			sanguis::server::space_unit
		>(
			500.F
		)
		&&
		sanguis::server::ai::make_path(
			this->context(),
			sanguis::server::world::center_to_grid_pos(
				start_pos_
			)
		);
}

sanguis::server::ai::status
sanguis::server::ai::behavior::stay::update(
	sanguis::duration
)
{
	return
		sanguis::server::ai::go_to_grid_pos(
			this->context(),
			fcppt::literal<
				sanguis::server::ai::speed_factor
			>(
				1
			)
		);
}
