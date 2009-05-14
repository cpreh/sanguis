#include "model_part.hpp"
#include "model_part_state.hpp"
#include "object.hpp"
#include "../load/model/part.hpp"
#include "../load/model/base_animation_not_found.hpp"
#include "../log.hpp"
#include "../exception.hpp"
#include <sge/console/var_impl.hpp>
#include <sge/math/abs_angle_to_rel.hpp>
#include <sge/math/rel_angle_to_abs.hpp>
#include <sge/math/is_rel_angle.hpp>
#include <sge/math/twopi.hpp>
#include <sge/math/vector/dim.hpp>
#include <sge/log/headers.hpp>
#include <sge/math/compare.hpp>
#include <sge/sprite/object.hpp>
#include <sge/time/time.hpp>
#include <sge/structure_cast.hpp>
#include <sge/text.hpp>
#include <boost/bind.hpp>
#include <algorithm>
#include <limits>
#include <cmath>

namespace
{

sge::sprite::rotation_type const
invalid_rotation(
	std::numeric_limits<sge::sprite::rotation_type>::max());
}

sanguis::draw::model_part::model_part(
	load::model::part const& info,
	sanguis::draw::object &ref)
:
	anim_diff_clock(),
	desired_orientation(
		invalid_rotation),
	info(&info),
	ref(&ref),
	weapon_(weapon_type::none),
	state(),
	animation_(),
	ended(false)
{
	ref.size() = sge::structure_cast<
		sge::sprite::dim
	>(
		info
		[weapon_type::none]
		[animation_type::none]
		.get().dim());
}

sanguis::draw::model_part::~model_part()
{}

bool sanguis::draw::model_part::animation(
	animation_type::type const atype)
{
	return state && state->animation_type() == atype
	? true
	: try_animation(
		atype);
}

void sanguis::draw::model_part::weapon(
	weapon_type::type const wtype)
{
	// we lose the animation here
	// which model has to reset
	//state.reset(new model_part_state(*info,animation_type::size,wtype));
	weapon_ = wtype;
	state.reset();
}

void sanguis::draw::model_part::update(
	time_type const time)
{
	anim_diff_clock.update(
		time);
	
	if (state)
		state->update();

	if(animation_)
		ended = animation_->process() || ended;

	if(sge::math::compare(desired_orientation, invalid_rotation))
		return;
	
	if(sge::math::compare(orientation(), desired_orientation))
		return;

	funit const
		// current orientation in [0,2pi]
		abs_current(
			sge::math::rel_angle_to_abs(
				orientation())),
		// target orientation in [0,2pi]
		abs_target(
			sge::math::rel_angle_to_abs(
				desired_orientation));
	
	// shortcut
	funit const twopi = sge::math::twopi<funit>();

	// TODO: those could be removed, should be asserted in rel_angle_to_abs?
	SGE_ASSERT(
		abs_current >= static_cast<funit>(0) && 
		abs_current <= twopi);
	SGE_ASSERT(
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

	SGE_ASSERT(
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
		sge::math::twopi<sanguis::draw::funit>();

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
		if (new_orientation < desired_orientation)
		{
			update_orientation(
				sge::math::abs_angle_to_rel(
					new_orientation));
		}
		else
		{
			update_orientation(
				desired_orientation);
		}
	}
	else
	{
		if (new_orientation > desired_orientation)
		{
			update_orientation(
				sge::math::abs_angle_to_rel(
					new_orientation));
		}
		else
		{
			update_orientation(
				desired_orientation);
		}
	}
}

void sanguis::draw::model_part::orientation(
	sge::sprite::rotation_type rot)
{
	if(!sge::math::is_rel_angle(rot))
		rot = sge::math::abs_angle_to_rel(rot);

	if(sge::math::compare(desired_orientation, invalid_rotation))
		update_orientation(rot);
	desired_orientation = rot;
}

bool sanguis::draw::model_part::animation_ended() const
{
	return ended;
}

sanguis::draw::object &sanguis::draw::model_part::object()
{
	return *ref;
}

sanguis::draw::object const &sanguis::draw::model_part::object() const
{
	return *ref;
}

bool sanguis::draw::model_part::try_animation(
	animation_type::type const atype)
{
	try
	{
		if (weapon_ == weapon_type::size)
			weapon_ = weapon_type::none;

		scoped_texture_animation nanim(	
			get_animation(
				state ? state->weapon_type() : weapon_,
				atype));

		animation_.swap(nanim);
	}
	catch(load::model::base_animation_not_found const &)
	{
		/*
		SGE_LOG_DEBUG(
			log(),
			sge::log::_1 << SGE_TEXT("didn't work"));
			*/
		return false;
	}

	/*
	SGE_LOG_DEBUG(
		log(),
		sge::log::_1 << SGE_TEXT("that worked"));
			*/
	ended = false;
	state.reset(
		new model_part_state(
			*info,
			*this,
			atype,
			state
			? state->weapon_type()
			: weapon_));
	return true;
}

sanguis::draw::model_part::animation_auto_ptr
sanguis::draw::model_part::get_animation(
	weapon_type::type const wtype,
	animation_type::type const atype)
{
	return animation_auto_ptr(
		new sge::sprite::texture_animation(
			(*info)[wtype]
				[atype]
					.get(),
			loop_method(
				atype),
			*ref,
			anim_diff_clock.callback()));
}

void sanguis::draw::model_part::update_orientation(
	sge::sprite::rotation_type const rot)
{
	ref->rotation(rot);
}

sge::sprite::texture_animation::loop_method::type
sanguis::draw::model_part::loop_method(
	animation_type::type const atype)
{
	switch(atype) {
	case animation_type::none:
	case animation_type::walking:
	case animation_type::attacking:
	case animation_type::reloading:
		return sge::sprite::texture_animation::loop_method::repeat;
	case animation_type::dying:
	case animation_type::deploying:
		return sge::sprite::texture_animation::loop_method::stop_at_end;
	default:
		throw sge::exception(
			SGE_TEXT("Invalid animation_type in model_part!"));
	}
}

sge::sprite::rotation_type
sanguis::draw::model_part::orientation() const
{
	return ref->rotation();
}
