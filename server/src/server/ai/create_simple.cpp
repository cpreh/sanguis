#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/ai/context_fwd.hpp>
#include <sanguis/server/ai/create_function.hpp>
#include <sanguis/server/ai/create_simple.hpp>
#include <sanguis/server/ai/sight_range.hpp>
#include <sanguis/server/ai/speed_factor.hpp>
#include <sanguis/server/ai/behavior/attack.hpp>
#include <sanguis/server/ai/behavior/wander.hpp>
#include <sanguis/server/ai/tree/base.hpp>
#include <sanguis/server/ai/tree/container.hpp>
#include <sanguis/server/ai/tree/make_leaf.hpp>
#include <sanguis/server/ai/tree/priority_sequence.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_literal_strong_typedef.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/container/make.hpp>


sanguis::server::ai::create_function
sanguis::server::ai::create_simple(
	sanguis::random_generator &_random_generator,
	sanguis::server::ai::sight_range const _sight_range
)
{
	return
		sanguis::server::ai::create_function{
			[
				&_random_generator,
				_sight_range
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
							fcppt::container::make<
								sanguis::server::ai::tree::container
							>(
								sanguis::server::ai::tree::make_leaf<
									sanguis::server::ai::behavior::attack
								>(
									_context,
									_sight_range
								),
								sanguis::server::ai::tree::make_leaf<
									sanguis::server::ai::behavior::wander
								>(
									_context,
									_random_generator,
									fcppt::literal<
										sanguis::server::ai::speed_factor
									>(
										0.3f
									)
								)
							)
						)
					);
			}
		};
}
