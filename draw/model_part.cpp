#include "model_part.hpp"
#include "../load/model/part.hpp"
#include <sge/exception.hpp>
#include <sge/string.hpp>
#include <boost/none.hpp>

sanguis::draw::model_part::model_part(
	load::model::part const& info,
	sge::sprite::object &ref)
: info(&info),
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
	case animation_type::attacking:
		if(!ended)
			return;
	case animation_type::dying:
		return;
	default:
		animation_type_ = anim_type;
		update_animation();
	}
}

void sanguis::draw::model_part::weapon(
	const weapon_type::type weap_type)
{
	weapon_type_ = weap_type;
	update_animation();
}

void sanguis::draw::model_part::update()
{
	ended = animation_.process();
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

sge::sprite::texture_animation::loop_method::type
sanguis::draw::model_part::loop_method() const
{
	switch(animation_type_) {
	case animation_type::none:
	case animation_type::walking:
		return sge::sprite::texture_animation::loop_method::repeat;
	case animation_type::attacking:
		return sge::sprite::texture_animation::loop_method::stop_after_end;
	case animation_type::dying:
		return sge::sprite::texture_animation::loop_method::stop_at_end;
	default:
		throw sge::exception(SGE_TEXT("Invalid animation_type in model_part!"));
	}
}
