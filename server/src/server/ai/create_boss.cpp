#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/ai/context_fwd.hpp>
#include <sanguis/server/ai/create_boss.hpp>
#include <sanguis/server/ai/create_function.hpp>
#include <sanguis/server/ai/sight_range.hpp>
#include <sanguis/server/ai/behavior/attack.hpp>
#include <sanguis/server/ai/behavior/patrol.hpp>
#include <sanguis/server/ai/behavior/stay.hpp>
#include <sanguis/server/ai/tree/base.hpp>
#include <sanguis/server/ai/tree/container.hpp>
#include <sanguis/server/ai/tree/make_leaf.hpp>
#include <sanguis/server/ai/tree/priority_sequence.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/assign/make_container.hpp>


sanguis::server::ai::create_function
sanguis::server::ai::create_boss(
	sanguis::random_generator &_random_generator,
	sanguis::server::ai::sight_range const _sight_range
)
{
	return
		sanguis::server::ai::create_function{
			[
				_sight_range,
				&_random_generator
			](
				sanguis::server::ai::context &_context
			)
			{
				return
					fcppt::unique_ptr_to_base<
						sanguis::server::ai::tree::base
					>(
						fcppt::make_unique_ptr<
							sanguis::server::ai::tree::priority_sequence
						>(
							fcppt::assign::make_container<
								sanguis::server::ai::tree::container
							>(
								sanguis::server::ai::tree::make_leaf<
									sanguis::server::ai::behavior::stay
								>(
									_context
								)
							)(
								sanguis::server::ai::tree::make_leaf<
									sanguis::server::ai::behavior::attack
								>(
									_context,
									_sight_range
								)
							)(
								sanguis::server::ai::tree::make_leaf<
									sanguis::server::ai::behavior::patrol
								>(
									_context,
									_random_generator
								)
							)
						)
					);
			}
		};
}
