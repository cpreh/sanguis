#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/ai/context_fwd.hpp>
#include <sanguis/server/ai/create_attack_health.hpp>
#include <sanguis/server/ai/create_function.hpp>
#include <sanguis/server/ai/sight_range.hpp>
#include <sanguis/server/ai/speed_factor.hpp>
#include <sanguis/server/ai/behavior/attack_health.hpp>
#include <sanguis/server/ai/behavior/wander.hpp>
#include <sanguis/server/ai/tree/container.hpp>
#include <sanguis/server/ai/tree/make_leaf.hpp>
#include <sanguis/server/ai/tree/priority_sequence.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_literal_strong_typedef.hpp>
#include <fcppt/make_unique_ptr_fcppt.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/assign/make_container.hpp>


sanguis::server::ai::create_function
sanguis::server::ai::create_attack_health(
	sanguis::random_generator &_random_generator,
	sanguis::server::ai::sight_range const _sight_range
)
{
	// TODO: Maybe create a common factor function for this
	return
		[
			&_random_generator,
			_sight_range
		](
			sanguis::server::ai::context &_context
		)
		{
			auto const speed_factor(
				fcppt::literal<
					sanguis::server::ai::speed_factor
				>(
					0.3f
				)
			);

			return
				fcppt::unique_ptr_to_base<
					sanguis::server::ai::tree::base
				>(
					fcppt::make_unique_ptr_fcppt<
						sanguis::server::ai::tree::priority_sequence
					>(
						fcppt::assign::make_container<
							sanguis::server::ai::tree::container
						>(
							sanguis::server::ai::tree::make_leaf<
								sanguis::server::ai::behavior::attack_health
							>(
								_context,
								_sight_range,
								speed_factor
							)
						)(
							sanguis::server::ai::tree::make_leaf<
								sanguis::server::ai::behavior::wander
							>(
								_context,
								_random_generator,
								speed_factor
							)
						)
					)
				);
		};
}
