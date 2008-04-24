#include "model_part.hpp"
#include "../load/model/part.hpp"
#include <sge/exception.hpp>
#include <sge/string.hpp>
#include <sge/console/console.hpp>
#include <sge/math/angle.hpp>
#include <sge/math/constants.hpp>
#include <sge/math/vec_dim.hpp>
#include <sge/math/compare.hpp>
#include <sge/sprite/object.hpp>
#include <limits>

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
	sge::sprite::object &ref)
: desired_orientation(
	invalid_rotation),
  info(&info),
  ref(&ref),
  animation_type_(animation_type::none),
  weapon_type_(weapon_type::none),
  animation_(
  	info[weapon_type_]
		[animation_type_]
			.get(),
	loop_method()),
  ended(false)
{
	update_animation();
}

void sanguis::draw::model_part::animation(
	const animation_type::type anim_type)
{
	// don't restart an animation unecessarly
	if(animation_type_ == anim_type)
		return;
	switch(animation_type_) {
	case animation_type::dying:
		return;
	case animation_type::attacking:
		if(!ended)
			return;
	default:
		animation_type_ = anim_type;
		update_animation();
	}
}

void sanguis::draw::model_part::weapon(
	const weapon_type::type weap_type)
{
	// don't restart an animation unecessarly
	if(weapon_type_ == weap_type)
		return;
	weapon_type_ = weap_type;
	update_animation();
}

void sanguis::draw::model_part::update(
	const time_type time)
{
	ended = animation_.process();

	if(sge::math::compare(desired_orientation, invalid_rotation))
		return;

	const sge::space_unit abs_angle = sge::math::rel_angle_to_abs(orientation()),
	                      abs_target = sge::math::rel_angle_to_abs(desired_orientation);
	
	const sge::space_unit twopi = sge::su(2)*sge::math::pi<sge::space_unit>();

	assert(abs_angle >= sge::su(0) && abs_angle <= twopi);
	assert(abs_target >= sge::su(0) && abs_target <= twopi);

	const sge::space_unit abs_dist = sge::math::abs(abs_target - abs_angle);
	const sge::space_unit swap_dist = (abs_angle > abs_target) ? twopi-abs_angle+abs_target : twopi-abs_target+abs_angle;
	const sge::space_unit min_dist = std::min(swap_dist,abs_dist);

	assert(abs_dist >= sge::su(0) && swap_dist >= sge::su(0) && min_dist >= sge::su(0));

	sge::space_unit dir;
	if (abs_angle > abs_target)
		dir = (swap_dist > abs_dist) ? sge::su(-1) : sge::su(1);
	else
		dir = (swap_dist > abs_dist) ? sge::su(1) : sge::su(-1);

	const sge::space_unit turning_speed = rotation_speed.value();

	sge::space_unit new_angle;

	if (min_dist < time/turning_speed)
		new_angle = desired_orientation;
	else
		new_angle = sge::math::abs_angle_to_rel(abs_angle + dir * time * turning_speed);

	update_orientation(new_angle);
}

void sanguis::draw::model_part::orientation(
	const sge::sprite::rotation_type rot)
{
	if(sge::math::compare(desired_orientation, invalid_rotation))
		update_orientation(rot);
	desired_orientation = rot;
}

void sanguis::draw::model_part::update_animation()
{
	animation_ = sge::sprite::texture_animation(
		(*info)[weapon_type_]
			[animation_type_]
				.get(),
		loop_method());
	animation_.bind(ref);
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
		return sge::sprite::texture_animation::loop_method::repeat;
	case animation_type::attacking:
		return sge::sprite::texture_animation::loop_method::stop_at_end;
	case animation_type::dying:
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
