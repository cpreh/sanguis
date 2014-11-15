#include <sanguis/duration.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/server/ai/context.hpp>
#include <sanguis/server/ai/go_to_grid_pos.hpp>
#include <sanguis/server/ai/make_path.hpp>
#include <sanguis/server/ai/speed_factor.hpp>
#include <sanguis/server/ai/behavior/base.hpp>
#include <sanguis/server/ai/behavior/status.hpp>
#include <sanguis/server/ai/behavior/wander.hpp>
#include <sanguis/server/random/grid_pos.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_literal_strong_typedef.hpp>


sanguis::server::ai::behavior::wander::wander(
	sanguis::server::ai::context &_context,
	sanguis::random_generator &_random_generator
)
:
	sanguis::server::ai::behavior::base(),
	context_(
		_context
	),
	random_generator_(
		_random_generator
	)
{
}

sanguis::server::ai::behavior::wander::~wander()
{
}

bool
sanguis::server::ai::behavior::wander::do_start()
{
	return
		sanguis::server::ai::make_path(
			context_,
			sanguis::server::random::grid_pos(
				random_generator_,
				sanguis::creator::pos::null(),
				context_.grid().size()
			)
		);
}

void
sanguis::server::ai::behavior::wander::do_stop()
{
	context_.clear_path();
}

sanguis::server::ai::behavior::status
sanguis::server::ai::behavior::wander::update(
	sanguis::duration
)
{
	return
		sanguis::server::ai::go_to_grid_pos(
			context_,
			fcppt::literal<
				sanguis::server::ai::speed_factor
			>(
				0.3f
			)
		);
}
