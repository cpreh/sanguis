#include <sanguis/server/ai/base.hpp>
#include <sanguis/server/ai/entity_set.hpp>
#include <sanguis/server/ai/optional_target.hpp>
#include <sanguis/server/ai/update_result.hpp>
#include <sanguis/server/ai/search_new_target.hpp>
#include <sanguis/server/ai/simple.hpp>
#include <sanguis/server/ai/sight_range.hpp>
#include <sanguis/server/ai/target.hpp>
#include <sanguis/server/ai/visible.hpp>
#include <sanguis/server/collision/distance_entity_entity.hpp>
#include <sanguis/server/entities/auto_weak_link.hpp>
#include <sanguis/server/entities/same_object.hpp>
#include <sanguis/server/entities/with_ai.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/with_links.hpp>
#include <sanguis/server/entities/property/change_event.hpp>
#include <sanguis/server/entities/property/value.hpp>
#include <fcppt/literal.hpp>


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

sanguis::server::ai::update_result
sanguis::server::ai::simple::new_target(
	sanguis::server::entities::auto_weak_link const &_target
)
{
	if(
		target_
		==
		_target
	)
		return
			sanguis::server::ai::update_result::keep_target;

	target_	 =
		_target;

	return
		sanguis::server::ai::update_result::change_target;
}

sanguis::server::ai::optional_target const
sanguis::server::ai::simple::target() const
{
	return
		target_
		?
			sanguis::server::ai::optional_target(
				sanguis::server::ai::target(
					target_->center()
				)
			)
		:
			sanguis::server::ai::optional_target()
		;
}

sanguis::server::entities::auto_weak_link
sanguis::server::ai::simple::entity_target() const
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
			sanguis::server::ai::update_result::keep_target
		;
}

sanguis::server::ai::update_result
sanguis::server::ai::simple::on_health_change(
	sanguis::server::ai::entity_set const &_entities,
	sanguis::server::entities::property::change_event const &_event
)
{
	if(
		_event.diff().get()
		>
		fcppt::literal<
			sanguis::server::entities::property::value
		>(
			0
		)
		||
		target_
	)
		return
			sanguis::server::ai::update_result::keep_target;

	sanguis::server::entities::auto_weak_link const result(
		sanguis::server::ai::search_new_target(
			me_,
			_entities
		)
	);

	return
		result
		?
			this->update_target(
				dynamic_cast<
					sanguis::server::entities::with_body &
				>(
					*result
				)
			)
		:
			sanguis::server::ai::update_result::keep_target
		;
}

sanguis::server::ai::update_result
sanguis::server::ai::simple::update_target(
	sanguis::server::entities::with_body &_entity
)
{
	return
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
		?
			this->new_target(
				_entity.link()
			)
		:
			sanguis::server::ai::update_result::keep_target
		;
}

sanguis::server::ai::update_result
sanguis::server::ai::simple::lose_target(
	sanguis::server::entities::with_body &_entity
)
{
	if(
		target_
		&&
		sanguis::server::entities::same_object(
			*target_,
			_entity
		)
	)
	{
		target_.unlink();

		return
			sanguis::server::ai::update_result::change_target;
	}

	return
		sanguis::server::ai::update_result::keep_target;
}

sanguis::server::entities::with_ai const &
sanguis::server::ai::simple::me() const
{
	return
		me_;
}
