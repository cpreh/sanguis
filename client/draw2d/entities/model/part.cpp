#include "part.hpp"
#include "part_state.hpp"
#include "../../sprite/dim.hpp"
#include "../../sprite/rotation_type.hpp"
#include "../../../../load/model/part.hpp"
#include "../../../../load/model/base_animation_not_found.hpp"
#include "../../../../load/model/animation_context.hpp"
#include "../../../../load/model/weapon_category.hpp"
#include "../../../../load/model/animation.hpp"
#include "../../../../exception.hpp"
#include "../../../../rel_angle_to_abs.hpp"
#include <sge/sprite/animation/texture_impl.hpp>
#include <sge/sprite/object_impl.hpp>
#include <fcppt/math/dim/structure_cast.hpp>
#include <fcppt/math/abs_angle_to_rel.hpp>
#include <fcppt/math/is_rel_angle.hpp>
#include <fcppt/math/twopi.hpp>
#include <fcppt/math/vector/dim.hpp>
#include <fcppt/math/compare.hpp>
#include <fcppt/text.hpp>
#include <algorithm>
#include <limits>
#include <cmath>

namespace
{

sanguis::client::draw2d::sprite::rotation_type const
invalid_rotation(
	std::numeric_limits<
		sanguis::client::draw2d::sprite::rotation_type
	>::max()
);

}

sanguis::client::draw2d::entities::model::part::part(
	load::model::part const& _load_part,
	sprite::normal::object &_ref
)
:
	anim_diff_clock_(),
	desired_orientation_(
		invalid_rotation
	),
	load_part_(
		_load_part
	),
	ref_(
		_ref
	),
	weapon_(
		weapon_type::none
	),
	state_(),
	animation_context_(),
	animation_(),
	ended_(
		false)
{
	ref_.size(
		sprite::dim::null()
	);
}

sanguis::client::draw2d::entities::model::part::~part()
{}

bool
sanguis::client::draw2d::entities::model::part::try_animation(
	animation_type::type const atype
)
{
	if (weapon_ == weapon_type::size)
		weapon_ = weapon_type::none;
	
	if (state_ && state_->animation_type() == atype)
		return true;
	
	if (!load_part_[weapon_].has_animation(atype))
		return false;

	load_animation(
		atype
	);

	return true;
}

void
sanguis::client::draw2d::entities::model::part::weapon(
	weapon_type::type const wtype
)
{
	// we lose the animation here
	// which model has to reset
	//state.reset(new model_part_state(*load_part,animation_type::size,wtype));
	weapon_ = wtype;
	state_.reset();
}

void
sanguis::client::draw2d::entities::model::part::update(
	time_type const time
)
{
	anim_diff_clock_.update(
		time);
	
	if (!animation_ && animation_context_)
	{
		animation_context_->update();
		if (animation_context_->is_finished())
		{
			animation_.reset(
				new sprite::normal::texture_animation(
					animation_context_->result(),
					loop_method(
						state_->animation_type()
					),
					ref_,
					anim_diff_clock_.callback()
				)
			);

			ref_.size(
				fcppt::math::dim::structure_cast<
					sprite::dim
				>(
					animation_->series().begin()->dim()
				) // TODO
			);
		}
	}
	
	if (state_)
		state_->update();

	if(animation_)
		ended_ = animation_->process() || ended_;

	if(fcppt::math::compare(desired_orientation_, invalid_rotation))
		return;
	
	if(fcppt::math::compare(orientation(), desired_orientation_))
		return;

	funit const
		// current orientation in [0,2pi]
		abs_current(
			rel_angle_to_abs(
				orientation()
			)
		),
		// target orientation in [0,2pi]
		abs_target(
			rel_angle_to_abs(
				desired_orientation_
			)
		);
	
	// shortcut
	funit const twopi = fcppt::math::twopi<funit>();

	// TODO: those could be removed, should be asserted in rel_angle_to_abs?
	FCPPT_ASSERT(
		abs_current >= static_cast<funit>(0) && 
		abs_current <= twopi);
	FCPPT_ASSERT(
		abs_target >= static_cast<funit>(0) && 
		abs_target <= twopi);

	// Explanation: we now have the current orientation ('c') and the target ('t')
	// angle on a "line":
	//
	// 0 |--------c------------t------------| 2pi
	// 
	//    ...dist    abs_dist           swap_...
	//
	// The abs_dist below is the "direct" distance from 'c' to 't'. The swap_dist
	// is the distance from 't' to 2pi (the "end") and from there - after
	// wrapping to the origin - to 'c'. Of course, 'c' could also be greater than
	// 't', hence the if test in swap_dist.
	//

	funit const
		// this is the "inner distance" from 
		abs_dist = std::abs(abs_target - abs_current),
		swap_dist = (abs_current > abs_target) 
			? twopi-abs_current+abs_target 
			: twopi-abs_target+abs_current,
		min_dist = std::min(swap_dist,abs_dist);

	FCPPT_ASSERT(
		abs_dist >= static_cast<funit>(0) && 
		swap_dist >= static_cast<funit>(0) && 
		min_dist >= static_cast<funit>(0));

	// We go left or right, depending on:
	//
	// (i) which distance (abs_dist or swap_dist) is smaller
	// (ii) if the current orientation is greater than the target
	funit const dir
		= abs_current > abs_target
		? ((swap_dist > abs_dist) ? static_cast<funit>(-1) : static_cast<funit>(1))
		: ((swap_dist > abs_dist) ? static_cast<funit>(1) : static_cast<funit>(-1));

	funit const turning_speed = 
		fcppt::math::twopi<funit>();

	funit const new_orientation = 
		abs_current + dir * time * turning_speed;
	
	// This fixes the "epilepsy" bug. Imagine the current orientation being 10,
	// the desired orientation being 20 and "time" is relatively large in the
	// above assignment. So we might not get orientation values of 15 or 18
	// oder 20 in the next frame, but maybe 30. If the next frame is slow again,
	// the orientation is corrected "downwards" to 5 or 10 again, then upwards and
	// so on, causing epilepsy.
	if (dir > static_cast<funit>(0))
	{
		if (new_orientation < desired_orientation_)
		{
			update_orientation(
				fcppt::math::abs_angle_to_rel(
					new_orientation));
		}
		else
		{
			update_orientation(
				desired_orientation_);
		}
	}
	else
	{
		if (new_orientation > desired_orientation_)
		{
			update_orientation(
				fcppt::math::abs_angle_to_rel(
					new_orientation));
		}
		else
		{
			update_orientation(
				desired_orientation_);
		}
	}
}

void
sanguis::client::draw2d::entities::model::part::orientation(
	sprite::rotation_type rot
)
{
	if(!fcppt::math::is_rel_angle(rot))
		rot = fcppt::math::abs_angle_to_rel(rot);

	if(fcppt::math::compare(desired_orientation_, invalid_rotation))
		update_orientation(rot);

	desired_orientation_ = rot;
}

bool
sanguis::client::draw2d::entities::model::part::animation_ended() const
{
	return ended_;
}

sanguis::client::draw2d::sprite::normal::object &
sanguis::client::draw2d::entities::model::part::object()
{
	return ref_;
}

sanguis::client::draw2d::sprite::normal::object const &
sanguis::client::draw2d::entities::model::part::object() const
{
	return ref_;
}

void
sanguis::client::draw2d::entities::model::part::load_animation(
	animation_type::type const atype
)
{
	animation_.reset();
	animation_context_.take(
		load_part_[weapon_][atype].load());
	
	state_.reset(
		new part_state(
			load_part_,
			*this, // FIXME: this can be removed now
			atype,
			weapon_
		)
			/*
			state_
				? state_->weapon_type()
				: weapon_)*/
	);
}

void
sanguis::client::draw2d::entities::model::part::update_orientation(
	sprite::rotation_type const rot
)
{
	ref_.rotation(
		rot
	);
}

sge::sprite::animation::loop_method::type
sanguis::client::draw2d::entities::model::part::loop_method(
	animation_type::type const atype
)
{
	switch(atype)
	{
	case animation_type::none:
	case animation_type::walking:
	case animation_type::attacking:
	case animation_type::reloading:
		return sge::sprite::animation::loop_method::repeat;
	case animation_type::dying:
	case animation_type::deploying:
		return sge::sprite::animation::loop_method::stop_at_end;
	case animation_type::size:
		break;
	}

	throw sge::exception(
		FCPPT_TEXT("Invalid animation_type in model_part!")
	);
}

sanguis::client::draw2d::sprite::rotation_type
sanguis::client::draw2d::entities::model::part::orientation() const
{
	return ref_.rotation();
}
