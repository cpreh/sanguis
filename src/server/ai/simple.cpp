#include <sanguis/server/ai/base.hpp>
#include <sanguis/server/ai/update_result.hpp>
#include <sanguis/server/ai/simple.hpp>
#include <sanguis/server/ai/sight_range.hpp>
#include <sanguis/server/ai/visible.hpp>
#include <sanguis/server/collision/distance_entity_entity.hpp>
#include <sanguis/server/entities/auto_weak_link.hpp>
#include <sanguis/server/entities/same_object.hpp>
#include <sanguis/server/entities/with_ai.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/with_links.hpp>


sanguis::server::ai::simple::simple(
	sanguis::server::entities::with_ai &_me,
	sanguis::server::ai::sight_range const _sight_range
)
:
	sanguis::server::ai::simple::base(),
	me_(
		_me
	),
	sight_range_(
		_sight_range
	),
	target_()
{
}

sanguis::server::ai::simple::~simple()
{
}

sanguis::server::entities::auto_weak_link
sanguis::server::ai::simple::target() const
{
	return
		target_;
}

sanguis::server::ai::sight_range const
sanguis::server::ai::simple::sight_range() const
{
	return
		sight_range_;
}

sanguis::server::ai::update_result
sanguis::server::ai::simple::in_range(
	sanguis::server::entities::with_body &_entity
)
{
	return
		sanguis::server::ai::update_result::keep_target;
}

sanguis::server::ai::update_result
sanguis::server::ai::simple::out_of_range(
	sanguis::server::entities::with_body &_entity
)
{
	return
		this->lose_target(
			_entity
		);
}

sanguis::server::ai::update_result
sanguis::server::ai::simple::distance_changes(
	sanguis::server::entities::with_body &_entity,
	sanguis::server::ai::visible const _visible
)
{
	return
		_visible.get()
		?
			this->update_target(
				_entity
			)
		:
			sanguis::server::ai::update_result::keep_target;
}

sanguis::server::ai::update_result
sanguis::server::ai::simple::update_target(
	sanguis::server::entities::with_body &_entity
)
{
	if(
		!target_
		||
		(
			target_
			&&
			sanguis::server::collision::distance_entity_entity(
				me_,
				_entity
			)
			<
			sanguis::server::collision::distance_entity_entity(
				me_,
				*target_
			)
		)
	)
	{
		target_ = _entity.link();

		return
			sanguis::server::ai::update_result::new_target;
	}

	return
		sanguis::server::ai::update_result::keep_target;
}

sanguis::server::ai::update_result
sanguis::server::ai::simple::lose_target(
	sanguis::server::entities::with_body &_entity
)
{
	sanguis::server::ai::update_result const result(
		target_
		&&
		sanguis::server::entities::same_object(
			*target_,
			_entity
		)
		?
			sanguis::server::ai::update_result::lost_target
		:
			sanguis::server::ai::update_result::keep_target
	);

	if(
		result
		==
		sanguis::server::ai::update_result::lost_target
	)
		target_.unlink();

	return
		result;
}
