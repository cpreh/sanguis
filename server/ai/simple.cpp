#include "simple.hpp"
#include "../entities/entity_with_weapon.hpp"
#include "../entities/property.hpp"
#include "../collision/collides.hpp"
#include <sge/time/second.hpp>
#include <sge/time/resolution.hpp>
#include <sge/math/vector/angle_between.hpp>
#include <sge/optional.hpp>

sanguis::server::ai::simple::simple(
	entities::auto_weak_link owner_
)
:
	me_(0),
	target(),
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
	me_ = &me;
}

void
sanguis::server::ai::simple::update(
	time_type const time
)
{
#if 0
	diff_clock_.update(
		time
	);

	if(!me_)
		return;
	
	entities::entity_with_weapon &me(
		*me_);

	entities::property &speed(
		me.property(
			entities::property_type::movement_speed
		)
	);

	if(/*search_new_target_timer.update_b() ||*/ !target)
	{
		target = find_nearest_enemy(
			me,
			owner_
				? owner_->center()
				: me.center(),
			entities
		);

		if(!target)
		{
			me.aggressive(false);
			speed.current(
				static_cast<space_unit>(0));
			return;
		}

		me.aggressive(true);
	}

	sge::optional<space_unit> const angle(
		sge::math::vector::angle_between<space_unit>(
			me.center(),
			target->center()
		)
	);

	if(angle)
	{
		me.direction(*angle);
		me.angle(*angle);
	}
	
	if(collision::collides(*target, me))
		speed.current(
			static_cast<space_unit>(0));
	else
		speed.current_to_max();

	me.target(
		target->center());
#endif
}
