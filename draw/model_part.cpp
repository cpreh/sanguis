#include "model_part.hpp"
#include "../load/model/part.hpp"
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
	sge::sprite::texture_animation::loop_method::repeat) // FIXME
{
	animation_.bind(&ref);
}

void sanguis::draw::model_part::animation(
	const animation_type::type anim_type)
{
	// don't restart an animation unecessarly
	if(animation_type_ == anim_type)
		return;
	animation_type_ = anim_type;
	update_animation();
}

void sanguis::draw::model_part::weapon(
	const weapon_type::type weap_type)
{
	weapon_type_ = weap_type;
	update_animation();
}

void sanguis::draw::model_part::update()
{
	animation_.process();
}

void sanguis::draw::model_part::update_animation()
{
	const sge::sprite::texture_animation::loop_method::type method(
		sge::sprite::texture_animation::loop_method::repeat); // FIXME
	animation_ = sge::sprite::texture_animation(
		(*info)[weapon_type_]
			[animation_type_]
				.get(),
		method);
	animation_.bind(ref);
}
