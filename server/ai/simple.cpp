#include "simple.hpp"
#include "search_new_target.hpp"
#include "../auras/aggro.hpp"
#include "../auras/auto_ptr.hpp"
#include "../entities/with_ai.hpp"
#include "../entities/movable.hpp"
#include "../entities/base.hpp"
#include "../entities/property/current_to_max.hpp"
#include "../collision/collides.hpp"
#include "../collision/distance.hpp"
#include <sge/math/vector/angle_between.hpp>
#include <sge/container/map_impl.hpp>
#include <sge/make_auto_ptr.hpp>
#include <sge/optional.hpp>
#include <sge/assert.hpp>
#include <tr1/functional>

sanguis::server::ai::simple::simple(
	entities::with_ai &me_,
	entities::auto_weak_link owner_
)
:
	me_(me_),
	target_(),
	owner_(owner_),
	potential_targets_()
{
	auras::auto_ptr new_aura(
		sge::make_auto_ptr<
			auras::aggro
		>(
			1000, // FIXME
			me_.team(),
			std::tr1::bind(
				&simple::target_enters,
				this,
				std::tr1::placeholders::_1
			),
			std::tr1::bind(
				&simple::target_leaves,
				this,
				std::tr1::placeholders::_1
			)
		)
	);

	me_.add_aura(
		new_aura
	);
}

void
sanguis::server::ai::simple::update(
	time_type const
)
{
	if(
		!target_ && potential_targets_.empty()
	)
	{
		me_.aggressive(
			false
		);

		return;
	}

	if(
		!target_
	)
		target_
			= search_new_target(
				me_,
				owner_,
				potential_targets_
			);

	SGE_ASSERT(
		target_
	);

	sge::optional<
		space_unit
	> const angle(
		sge::math::vector::angle_between<
			space_unit
		>(
			me_.center(),
			target_->center()
		)
	);

	if(angle)
		me_.angle(
			*angle
		);

	entities::movable *const movable_(
		dynamic_cast<
			entities::movable *
		>(
			&me_
		)
	);

	if(
		movable_
	)
	{
		entities::property::changeable &speed(
			movable_->movement_speed()
		);

		if(angle)
			movable_->direction(
				*angle
			);
	
		// don't walk into the enemy
		// TODO: this should be done with the collision system
		if(
			collision::collides(
				*target_,
				me_
			)
		)
			speed.current(
				0
			);
		else
			entities::property::current_to_max(
				speed
			);
	}

	me_.aggressive(
		true
	);

	me_.target(
		target_->center()
	);
}

void
sanguis::server::ai::simple::target_enters(
	entities::base &new_target
)
{
	potential_targets_.insert(
		new_target.id(),
		new_target.link()
	);
		
	if(
		target_
	)
		return;
	
	// if we already have a target
	// and the new target is farther away
	// do nothing
	if(
		target_
		&& collision::distance(
			*target_,
			me_
		)
		> collision::distance(
			new_target,
			me_
		)
	)
		return;
			
	target_ = new_target.link();
}

void
sanguis::server::ai::simple::target_leaves(
	entities::base &old_target
)
{
	potential_targets_.erase(
		old_target.id()
	);
}
