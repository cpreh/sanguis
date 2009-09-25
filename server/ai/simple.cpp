#include "simple.hpp"
#include "search_new_target.hpp"
#include "../auras/aggro.hpp"
#include "../auras/auto_ptr.hpp"
#include "../entities/with_weapon.hpp"
#include "../entities/with_auras.hpp"
#include "../entities/movable.hpp"
#include "../entities/base.hpp"
#include "../entities/property.hpp"
#include "../collision/collides.hpp"
#include "../collision/distance.hpp"
#include <sge/math/vector/angle_between.hpp>
#include <sge/container/map_impl.hpp>
#include <sge/make_auto_ptr.hpp>
#include <sge/optional.hpp>
#include <sge/assert.hpp>
#include <boost/bind.hpp>

sanguis::server::ai::simple::simple(
	entities::auto_weak_link owner_
)
:
	me_(0),
	target_(),
	owner_(owner_),
	potential_targets_()
{}

void
sanguis::server::ai::simple::bind(
	entities::with_weapon &me
)
{
	SGE_ASSERT(!me_);

	me_ = &me;

	auras::auto_ptr new_aura(
		sge::make_auto_ptr<
			auras::aggro
		>(
			10, // FIXME
			me_->team(),
			boost::bind(
				&simple::target_enters,
				this,
				_1
			),
			boost::bind(
				&simple::target_leaves,
				this,
				_1
			)
		)
	);

	dynamic_cast<
		entities::with_auras &
	>(
		me
	)
	.add_aura(
		new_aura
	);
}

void
sanguis::server::ai::simple::update(
	time_type const
)
{
	SGE_ASSERT(me_);

	entities::with_weapon &me(
		*me_
	);

	if(
		!target_ && potential_targets_.empty()
	)
	{
		me.aggressive(
			false
		);

		return;
	}

	if(
		!target_
	)
		target_
			= search_new_target(
				me,
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
			me.center(),
			target_->center()
		)
	);

	if(angle)
		me.angle(
			*angle
		);

	entities::movable *const movable_(
		dynamic_cast<
			entities::movable *
		>(
			me_
		)
	);

	if(
		movable_
	)
	{
		entities::property &speed(
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
				me
			)
		)
			speed.current(
				static_cast<space_unit>(0)
			);
		else
			speed.current_to_max();
	}

	me.aggressive(
		true
	);

	me.target(
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
			*me_
		)
		> collision::distance(
			new_target,
			*me_
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
