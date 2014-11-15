#include <sanguis/duration.hpp>
#include <sanguis/server/add_target_callback.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/remove_target_callback.hpp>
#include <sanguis/server/ai/context.hpp>
#include <sanguis/server/ai/go_close_to_target.hpp>
#include <sanguis/server/ai/idle.hpp>
#include <sanguis/server/ai/sight_range.hpp>
#include <sanguis/server/ai/speed_factor.hpp>
#include <sanguis/server/ai/behavior/base.hpp>
#include <sanguis/server/ai/behavior/follow_friend.hpp>
#include <sanguis/server/ai/behavior/status.hpp>
#include <sanguis/server/auras/target.hpp>
#include <sanguis/server/auras/target_kind.hpp>
#include <sanguis/server/entities/auto_weak_link.hpp>
#include <sanguis/server/entities/same_object.hpp>
#include <sanguis/server/entities/with_ai.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/with_links.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_literal_strong_typedef.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sanguis::server::ai::behavior::follow_friend::follow_friend(
	sanguis::server::ai::context &_context,
	sanguis::server::ai::sight_range const _sight_range
)
:
	context_(
		_context
	),
	potential_targets_(),
	target_()
{
	_context.me().add_aura(
		fcppt::make_unique_ptr<
			sanguis::server::auras::target
		>(
			sanguis::server::radius(
				_sight_range.get()
			),
			context_.me().team(),
			sanguis::server::auras::target_kind::friend_,
			sanguis::server::add_target_callback(
				std::bind(
					&sanguis::server::ai::behavior::follow_friend::target_enters,
					this,
					std::placeholders::_1
				)
			),
			sanguis::server::remove_target_callback(
				std::bind(
					&sanguis::server::ai::behavior::follow_friend::target_leaves,
					this,
					std::placeholders::_1
				)
			)
		)
	);
}

sanguis::server::ai::behavior::follow_friend::~follow_friend()
{
}

bool
sanguis::server::ai::behavior::follow_friend::do_start()
{
	target_ =
		potential_targets_.empty()
		?
			sanguis::server::entities::auto_weak_link()
		:
			this->first_target()
		;

	return
		target_.has_value();
}

void
sanguis::server::ai::behavior::follow_friend::do_stop()
{
	context_.clear_path();

	target_ =
		sanguis::server::entities::auto_weak_link();

	sanguis::server::ai::idle(
		context_.me()
	);
}

sanguis::server::ai::behavior::status
sanguis::server::ai::behavior::follow_friend::update(
	sanguis::duration
)
{
	if(
		!target_
	)
		return
			sanguis::server::ai::behavior::status::failure;

	sanguis::server::ai::go_close_to_target(
		context_,
		sanguis::server::ai::target{
			target_->center()
		},
		fcppt::literal<
			sanguis::server::ai::speed_factor
		>(
			1
		)
	);

	return
		sanguis::server::ai::behavior::status::running;
}

void
sanguis::server::ai::behavior::follow_friend::target_enters(
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

	target_ =
		this->first_target();
}

void
sanguis::server::ai::behavior::follow_friend::target_leaves(
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

	if(
		target_
		&&
		sanguis::server::entities::same_object(
			*target_,
			_with_body
		)
	)
		target_ =
			sanguis::server::entities::auto_weak_link();
}

sanguis::server::entities::auto_weak_link
sanguis::server::ai::behavior::follow_friend::first_target() const
{
	FCPPT_ASSERT_PRE(
		!potential_targets_.empty()
	);

	return
		potential_targets_.begin()->get().link();
}
