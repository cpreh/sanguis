#include <sanguis/server/ai/sight_range.hpp>
#include <sanguis/server/ai/simple.hpp>
#include <sanguis/server/ai/swarm.hpp>
#include <sanguis/server/ai/update_result.hpp>
#include <sanguis/server/ai/pathing/is_visible.hpp>
#include <sanguis/server/entities/auto_weak_link.hpp>
#include <sanguis/server/entities/optional_with_ai_ref.hpp>
#include <sanguis/server/entities/with_ai.hpp>
#include <sanguis/server/entities/with_ai_ref.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/with_links.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/world/center_to_grid_pos.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/try_dynamic_cast.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/cast/static_downcast.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sanguis::server::ai::swarm::swarm(
	sanguis::server::entities::with_ai &_me,
	sanguis::server::ai::sight_range const _sight_range
)
:
	sanguis::server::ai::simple(
		_me,
		_sight_range
	),
	friends_()
{
}

sanguis::server::ai::swarm::~swarm()
{
}

sanguis::server::ai::update_result
sanguis::server::ai::swarm::friend_in_range(
	sanguis::server::entities::with_body &_with_body
)
{
	this->dispatch_swarm_ai(
		_with_body,
		[
			this
		](
			sanguis::server::entities::with_ai &with_ai
		)
		{
			FCPPT_ASSERT_ERROR(
				friends_.insert(
					fcppt::make_ref(
						with_ai
					)
				).second
			);
		}
	);

	return
		this->follow_leader();
}

sanguis::server::ai::update_result
sanguis::server::ai::swarm::friend_out_of_range(
	sanguis::server::entities::with_body &_with_body
)
{
	this->dispatch_swarm_ai(
		_with_body,
		[
			this
		](
			sanguis::server::entities::with_ai &with_ai
		)
		{
			FCPPT_ASSERT_ERROR(
				friends_.erase(
					fcppt::make_ref(
						with_ai
					)
				)
				==
				1u
			);
		}
	);

	return
		this->follow_leader();
}

sanguis::server::ai::update_result
sanguis::server::ai::swarm::update_target(
	sanguis::server::entities::with_body &_target
)
{
	sanguis::server::ai::update_result const base_result(
		sanguis::server::ai::simple::update_target(
			_target
		)
	);

	sanguis::server::ai::update_result const leader_result(
		this->follow_leader()
	);

	return
		leader_result
		==
		sanguis::server::ai::update_result::keep_target
		?
			leader_result
		:
			base_result
		;
}

bool
sanguis::server::ai::swarm::aggressive() const
{
	return
		this->entity_target()
		&&
		this->entity_target()->team()
		!=
		this->me().team();
}

bool
sanguis::server::ai::swarm::target_friends() const
{
	return
		true;
}

sanguis::server::entities::optional_with_ai_ref const
sanguis::server::ai::swarm::leader() const
{
	if(
		friends_.empty()
	)
		return
			sanguis::server::entities::optional_with_ai_ref();

	sanguis::server::entities::with_ai_ref const with_ai(
		*friends_.begin()
	);

	return
		std::less<
			sanguis::server::entities::with_ai const *
		>()(
			with_ai.get_pointer(),
			&this->me()
		)
		?
			sanguis::server::entities::optional_with_ai_ref(
				with_ai.get()
			)
		:
			sanguis::server::entities::optional_with_ai_ref()
		;
}


sanguis::server::ai::update_result
sanguis::server::ai::swarm::follow_leader()
{
	sanguis::server::entities::optional_with_ai_ref const cur_leader(
		this->leader()
	);

	if(
		!cur_leader
	)
		return
			sanguis::server::ai::update_result::keep_target;

	sanguis::server::ai::swarm const &leader_ai(
		fcppt::cast::static_downcast<
			sanguis::server::ai::swarm const &
		>(
			cur_leader->ai()
		)
	);

	sanguis::server::entities::auto_weak_link const leader_target(
		leader_ai.entity_target()
	);

	bool const leader_target_visible(
		leader_target
		&&
		sanguis::server::ai::pathing::is_visible(
			this->me().environment()->grid(),
			sanguis::server::world::center_to_grid_pos(
				this->me().center()
			),
			sanguis::server::world::center_to_grid_pos(
				leader_target->center()
			)
		)
	);

	if(
		this->aggressive()
		&&
		!leader_target_visible
	)
		return
			sanguis::server::ai::update_result::keep_target;

	return
		this->new_target(
			leader_target_visible
			?
				leader_target
			:
				cur_leader->link()
		);
}

template<
	typename Function
>
void
sanguis::server::ai::swarm::dispatch_swarm_ai(
	sanguis::server::entities::with_body &_with_body,
	Function const &_function
)
{
	FCPPT_TRY_DYNAMIC_CAST(
		sanguis::server::entities::with_ai *,
		with_ai,
		&_with_body
	)
		if(
			dynamic_cast<
				sanguis::server::ai::swarm const *
			>(
				&with_ai->ai()
			)
		)
			_function(
				*with_ai
			);
}
