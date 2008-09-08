#include "model_part.hpp"
#include "../load/model/part.hpp"
#include <sge/exception.hpp>
#include <sge/text.hpp>
#include <sge/console/var_impl.hpp>
#include <sge/math/angle.hpp>
#include <sge/math/constants.hpp>
#include <sge/math/vec_dim.hpp>
#include <sge/math/compare.hpp>
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
  animation_type_(animation_type::deploying),
  weapon_type_(weapon_type::none),
  animation_(),
  ended(false)
{
	update_animation();
	ref.size() = sge::math::structure_cast<sge::sprite::unit>(
		info
		[weapon_type::none]
		[animation_type::none]
		.get().dim());
}

void sanguis::draw::model_part::animation(
	animation_type::type const anim_type)
{
	// don't restart an animation unecessarly
	if(animation_type_ == anim_type)
		return;
	
	switch(animation_type_) {
	case animation_type::dying:
		return;
	// play those animations to the end
	case animation_type::attacking:
	case animation_type::deploying:
	case animation_type::reloading:
		if(!ended)
			return;
	default:
		animation_type_ = anim_type;
		update_animation();
	}
}

void sanguis::draw::model_part::weapon(
	weapon_type::type const weap_type)
{
	// don't restart an animation unecessarly
	if(weapon_type_ == weap_type)
		return;
	weapon_type_ = weap_type;
	update_animation();
}

void sanguis::draw::model_part::update(
	time_type const time)
{
	anim_diff_clock.update(
		time);

	ended = animation_->process() || ended;

	if(sge::math::compare(desired_orientation, invalid_rotation))
		return;

	const sge::space_unit abs_angle = sge::math::rel_angle_to_abs(orientation()),
	                      abs_target = sge::math::rel_angle_to_abs(desired_orientation);
	
	const sge::space_unit twopi = sge::math::twopi<sge::space_unit>();

	assert(abs_angle >= sge::su(0) && abs_angle <= twopi);
	assert(abs_target >= sge::su(0) && abs_target <= twopi);

	const sge::space_unit abs_dist = std::abs(abs_target - abs_angle),
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
	// FIXME: is this ok?
	if(!sge::math::is_rel_angle(rot))
		rot = sge::math::abs_angle_to_rel(rot);

	if(sge::math::compare(desired_orientation, invalid_rotation))
		update_orientation(rot);
	desired_orientation = rot;
}

void sanguis::draw::model_part::update_animation()
{
	animation_.reset(
		new sge::sprite::texture_animation(
			(*info)[weapon_type_]
				[animation_type_]
					.get(),
			loop_method(),
			ref->explicit_upcast(),
			anim_diff_clock.callback()));
	ended = false;
}

void sanguis::draw::model_part::update_orientation(
	const sge::sprite::rotation_type rot)
{
	ref->rotation(rot);
}

sge::sprite::texture_animation::loop_method::type
sanguis::draw::model_part::loop_method() const
{
	switch(animation_type_) {
	case animation_type::none:
	case animation_type::walking:
	case animation_type::attacking:
	case animation_type::reloading:
		return sge::sprite::texture_animation::loop_method::repeat;
	case animation_type::dying:
	case animation_type::deploying:
		return sge::sprite::texture_animation::loop_method::stop_at_end;
	default:
		throw sge::exception(SGE_TEXT("Invalid animation_type in model_part!"));
	}
}

sge::sprite::rotation_type
sanguis::draw::model_part::orientation() const
{
	return ref->rotation();
}
