#include "simple.hpp"
#include "../auras/aggro.hpp"
#include "../entities/entity_with_weapon.hpp"
#include "../entities/entity.hpp"
#include "../entities/property.hpp"
#include "../collision/collides.hpp"
#include "../collision/distance.hpp"
#include <sge/time/second.hpp>
#include <sge/time/resolution.hpp>
#include <sge/math/vector/angle_between.hpp>
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
	diff_clock_(),
	search_new_target_timer(
		sge::time::second(
			5
		),
		sge::time::activation_state::active,
		diff_clock_.callback()
	)
{}

void
sanguis::server::ai::simple::bind(
	entities::entity_with_weapon &me
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
				&simple::potential_target,
				this,
				_1
			)
		)
	);

	me_->add_aura(
		new_aura
	);
}

void
sanguis::server::ai::simple::update(
	time_type const time
)
{
	SGE_ASSERT(me_);

	diff_clock_.update(
		time
	);

	entities::entity_with_weapon &me(
		*me_
	);

	if(!target_)
	{
		me.aggressive(
			false
		);
		return;
	}
	
	entities::property &speed(
		me.property(
			entities::property_type::movement_speed
		)
	);

	sge::optional<space_unit> const angle(
		sge::math::vector::angle_between<space_unit>(
			me.center(),
			target_->center()
		)
	);

	if(angle)
	{
		me.direction(*angle);
		me.angle(*angle);
	}
	
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

	me.aggressive(
		true
	);

	me.target(
		target_->center()
	);
}

#include <iostream>

void
sanguis::server::ai::simple::potential_target(
	entities::entity &new_target
)
{
	std::cerr << "potential target " << new_target.id() << '\n';

	// if we already have a target
	// and the target timer hasn't elapsed
	// do nothing
	if(
		target_ && !search_new_target_timer.expired()
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
			
	search_new_target_timer.reset();
	target_ = new_target.link();
}
