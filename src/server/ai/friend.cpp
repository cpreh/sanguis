#include <sanguis/server/ai/friend.hpp>
#include <sanguis/server/ai/sight_range.hpp>
#include <sanguis/server/ai/simple.hpp>
#include <sanguis/server/ai/update_result.hpp>
#include <sanguis/server/entities/spawn_owner.hpp>
#include <sanguis/server/entities/with_ai_fwd.hpp>
#include <sanguis/server/entities/with_body.hpp>


sanguis::server::ai::friend_::friend_(
	sanguis::server::entities::with_ai &_me,
	sanguis::server::ai::sight_range const _sight_range,
	sanguis::server::entities::spawn_owner const &_spawn_owner
)
:
	sanguis::server::ai::simple(
		_me,
		_sight_range
	),
	spawn_owner_(
		_spawn_owner
	)
{
	this->new_target(
		spawn_owner_.get()
	);
}

sanguis::server::ai::friend_::~friend_()
{
}

sanguis::server::ai::update_result
sanguis::server::ai::friend_::lose_target(
	sanguis::server::entities::with_body &_with_body
)
{
	return
		spawn_owner_.get()
		?
			this->new_target(
				spawn_owner_.get()
			)
		:
			sanguis::server::ai::simple::lose_target(
				_with_body
			)
		;
}

sanguis::server::ai::update_result
sanguis::server::ai::friend_::update_target(
	sanguis::server::entities::with_body &_target
)
{
	return
		this->entity_target()
		==
		spawn_owner_.get()
		?
			this->new_target(
				_target.link()
			)
		:
			sanguis::server::ai::simple::update_target(
				_target
			)
		;
}

bool
sanguis::server::ai::friend_::aggressive() const
{
	return
		this->entity_target()
		!=
		spawn_owner_.get();
}

bool
sanguis::server::ai::friend_::does_patrolling() const
{
	return
		false;
}
