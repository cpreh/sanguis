#include <sanguis/duration.hpp>
#include <sanguis/server/ai/behavior/base.hpp>
#include <sanguis/server/ai/behavior/base_unique_ptr.hpp>
#include <sanguis/server/ai/behavior/status.hpp>
#include <sanguis/server/ai/tree/base.hpp>
#include <sanguis/server/ai/tree/leaf.hpp>
#include <sanguis/server/ai/tree/status.hpp>
#include <fcppt/assert/unreachable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::ai::tree::leaf::leaf(
	sanguis::server::ai::behavior::base_unique_ptr &&_behavior
)
:
	sanguis::server::ai::tree::base(),
	behavior_{
		std::move(
			_behavior
		)
	},
	started_{
		false
	}
{
}

sanguis::server::ai::tree::leaf::~leaf()
{
}

sanguis::server::ai::tree::status
sanguis::server::ai::tree::leaf::run(
	sanguis::duration const _duration
)
{
	if(
		!started_
	)
		started_ =
			behavior_->start();

	if(
		!started_
	)
		return
			sanguis::server::ai::tree::status::ended_failure;

	switch(
		behavior_->update(
			_duration
		)
	)
	{
	case sanguis::server::ai::behavior::status::running:
		return
			sanguis::server::ai::tree::status::running;

	case sanguis::server::ai::behavior::status::success:
		started_ =
			false;

		return
			sanguis::server::ai::tree::status::ended_success;
	case sanguis::server::ai::behavior::status::failure:
		started_ =
			false;

		return
			sanguis::server::ai::tree::status::ended_failure;
	}

	FCPPT_ASSERT_UNREACHABLE;
}
