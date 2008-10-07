#include "model_part.hpp"
#include "../load/model/part.hpp"
#include "../load/model/base_animation_not_found.hpp"
#include "../log.hpp"
#include "../exception.hpp"
#include <sge/text.hpp>
#include <sge/console/var_impl.hpp>
#include <sge/math/angle.hpp>
#include <sge/math/constants.hpp>
#include <sge/math/vec_dim.hpp>
#include <sge/log/headers.hpp>
#include <sge/math/compare.hpp>
#include <sge/audio/sound.hpp>
#include <sge/sprite/object.hpp>
#include <sge/time/time.hpp>
#include <boost/bind.hpp>
#include <algorithm>
#include <limits>
#include <cmath>

namespace
{

const sge::sprite::rotation_type invalid_rotation(
	std::numeric_limits<sge::sprite::rotation_type>::max());

sge::con::var<sge::space_unit> rotation_speed(
	SGE_TEXT("sprite_rot_speed"),
	sge::su(sge::math::pi<sge::space_unit>() * sge::su(2)));

}

sanguis::draw::model_part::model_part(
	load::model::part const& info,
	object &ref)
: anim_diff_clock(),
  desired_orientation(
	invalid_rotation),
  info(&info),
  ref(&ref),
	weapon_(weapon_type::none),
	state(),
  animation_(),
  ended(false)
{
	SGE_LOG_DEBUG(
		log(),
		sge::log::_1 << SGE_TEXT("constructing new model"));

	ref.size() = sge::math::structure_cast<sge::sprite::unit>(
		info
		[weapon_type::none]
		[animation_type::none]
		.get().dim());
}

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

	sge::space_unit const
		abs_angle(
			sge::math::rel_angle_to_abs(
				orientation())),
		abs_target(
			sge::math::rel_angle_to_abs(
				desired_orientation));
	
	sge::space_unit const twopi = sge::math::twopi<sge::space_unit>();

	assert(abs_angle >= sge::su(0) && abs_angle <= twopi);
	assert(abs_target >= sge::su(0) && abs_target <= twopi);

	sge::space_unit const
		abs_dist = std::abs(abs_target - abs_angle),
		swap_dist = (abs_angle > abs_target) ? twopi-abs_angle+abs_target : twopi-abs_target+abs_angle,
		min_dist = std::min(swap_dist,abs_dist);

	assert(abs_dist >= sge::su(0) && swap_dist >= sge::su(0) && min_dist >= sge::su(0));

	sge::space_unit const dir
		= abs_angle > abs_target
		? ((swap_dist > abs_dist) ? sge::su(-1) : sge::su(1))
		: ((swap_dist > abs_dist) ? sge::su(1) : sge::su(-1));

	sge::space_unit const turning_speed = rotation_speed.value();

	update_orientation(
		min_dist < time / turning_speed
		? desired_orientation
		: sge::math::abs_angle_to_rel(abs_angle + dir * time * turning_speed));
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
		SGE_LOG_DEBUG(
			log(),
			sge::log::_1 << SGE_TEXT("didn't work"));
		return false;
	}

	SGE_LOG_DEBUG(
		log(),
		sge::log::_1 << SGE_TEXT("that worked"));
	
	state.reset(new model_part_state(*info,atype,state ? state->weapon_type() : weapon_));
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
