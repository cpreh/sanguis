#include <sanguis/duration.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/creator/grid.hpp>
#include <sanguis/creator/min.hpp>
#include <sanguis/creator/pos.hpp>
#include <sanguis/creator/sup.hpp>
#include <sanguis/server/ai/context.hpp>
#include <sanguis/server/ai/go_to_grid_pos.hpp>
#include <sanguis/server/ai/make_path.hpp>
#include <sanguis/server/ai/speed_factor.hpp>
#include <sanguis/server/ai/status.hpp>
#include <sanguis/server/ai/behavior/base.hpp>
#include <sanguis/server/ai/behavior/wander.hpp>
#include <sanguis/server/random/grid_pos.hpp>
#include <fcppt/const.hpp>
#include <fcppt/maybe.hpp>
#include <fcppt/math/dim/to_vector.hpp>
#include <fcppt/math/vector/null.hpp>


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
		fcppt::maybe(
			sanguis::server::random::grid_pos(
				random_generator_,
				sanguis::creator::min{
					fcppt::math::vector::null<
						sanguis::creator::pos
					>()
				},
				sanguis::creator::sup{
					fcppt::math::dim::to_vector(
						this->context().grid().size()
					)
				}
			),
			fcppt::const_(
				false
			),
			[
				this
			](
				sanguis::creator::pos const _pos
			)
			{
				return
					sanguis::server::ai::make_path(
						this->context(),
						_pos
					);
			}
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
