#include <sanguis/server/health.hpp>
#include <sanguis/server/ai/context_fwd.hpp>
#include <sanguis/server/ai/sight_range.hpp>
#include <sanguis/server/ai/speed_factor.hpp>
#include <sanguis/server/ai/behavior/attack.hpp>
#include <sanguis/server/ai/behavior/attack_health.hpp>
#include <sanguis/server/entities/with_ai.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_literal_strong_typedef.hpp>
#include <fcppt/strong_typedef_construct_cast.hpp>
#include <fcppt/assert/pre.hpp>


sanguis::server::ai::behavior::attack_health::attack_health(
	sanguis::server::ai::context &_context,
	sanguis::server::ai::sight_range const _sight_range,
	sanguis::server::ai::speed_factor const _speed_factor
)
:
	sanguis::server::ai::behavior::attack{
		_context,
		_sight_range
	},
	speed_factor_{
		_speed_factor
	}
{
}

sanguis::server::ai::behavior::attack_health::~attack_health()
{
}

sanguis::server::ai::speed_factor const
sanguis::server::ai::behavior::attack_health::speed_factor() const
{
	FCPPT_ASSERT_PRE(
		this->me().max_health()
		>
		fcppt::literal<
			sanguis::server::health
		>(
			0.f
		)
	);

	return
		speed_factor_
		+
		fcppt::strong_typedef_construct_cast<
			sanguis::server::ai::speed_factor
		>(
			(
				fcppt::literal<
					sanguis::server::health
				>(
					1.0f
				)
				-
				this->me().current_health()
				/
				this->me().max_health()
			).get()
		);
}
