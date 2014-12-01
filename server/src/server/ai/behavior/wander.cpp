#include <sanguis/duration.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/server/ai/context.hpp>
#include <sanguis/server/ai/go_to_grid_pos.hpp>
#include <sanguis/server/ai/make_path.hpp>
#include <sanguis/server/ai/speed_factor.hpp>
#include <sanguis/server/ai/status.hpp>
#include <sanguis/server/ai/behavior/base.hpp>
#include <sanguis/server/ai/behavior/wander.hpp>
#include <sanguis/server/random/grid_pos.hpp>


sanguis::server::ai::behavior::wander::wander(
	sanguis::server::ai::context &_context,
	sanguis::random_generator &_random_generator,
	sanguis::server::ai::speed_factor const _speed_factor
)
:
	sanguis::server::ai::behavior::base(
		_context
	),
	random_generator_(
		_random_generator
	),
	speed_factor_{
		_speed_factor
	}
{
}

sanguis::server::ai::behavior::wander::~wander()
{
}

bool
sanguis::server::ai::behavior::wander::start()
{
	return
		sanguis::server::ai::make_path(
			this->context(),
			sanguis::server::random::grid_pos(
				random_generator_,
				sanguis::creator::pos::null(),
				this->context().grid().size()
			)
		);
}

sanguis::server::ai::status
sanguis::server::ai::behavior::wander::update(
	sanguis::duration
)
{
	return
		sanguis::server::ai::go_to_grid_pos(
			this->context(),
			speed_factor_
		);
}
