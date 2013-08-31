#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/ai/base.hpp>
#include <sanguis/server/ai/manager.hpp>
#include <sanguis/server/auras/aggro.hpp>
#include <sanguis/server/entities/with_ai.hpp>
#include <sanguis/server/entities/with_body_fwd.hpp>
#include <sge/timer/reset_when_expired.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <functional>
#include <fcppt/config/external_end.hpp>


sanguis::server::ai::manager::manager(
	sanguis::diff_clock const &_diff_clock,
	sanguis::server::ai::base &_ai,
	sanguis::server::entities::with_ai &_me
)
:
	ai_(
		_ai
	),
	potential_targets_(),
	update_timer_(
		sanguis::diff_timer::parameters(
			_diff_clock,
			std::chrono::milliseconds(
				500
			)
		)
		.expired(
			true
		)
	)
{
	_me.add_aura(
		fcppt::make_unique_ptr<
			sanguis::server::auras::aggro
		>(
			sanguis::server::radius(
				20.f // TODO
			),
			_me.team(),
			std::bind(
				&sanguis::server::ai::manager::target_enters,
				this,
				std::placeholders::_1
			),
			std::bind(
				&sanguis::server::ai::manager::target_leaves,
				this,
				std::placeholders::_1
			)
		)
	);
}

sanguis::server::ai::manager::~manager()
{
}

void
sanguis::server::ai::manager::update()
{
	if(
		!sge::timer::reset_when_expired(
			update_timer_
		)
	)
		return;

	// TODO: How should we track this?
	for(
		auto ref : potential_targets_
	)
		ai_.distance_changes(
			ref.get()
		);

	ai_.update();
}

void
sanguis::server::ai::manager::target_enters(
	sanguis::server::entities::with_body &_with_body
)
{
	FCPPT_ASSERT_ERROR(
		potential_targets_.insert(
			fcppt::make_ref(
				_with_body
			)
		)
		.second
	);

	ai_.in_range(
		_with_body
	);
}

void
sanguis::server::ai::manager::target_leaves(
	sanguis::server::entities::with_body &_with_body
)
{
	FCPPT_ASSERT_ERROR(
		potential_targets_.erase(
			fcppt::make_ref(
				_with_body
			)
		)
		==
		1u
	);

	ai_.out_of_range(
		_with_body
	);
}
