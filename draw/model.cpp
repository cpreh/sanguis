#include "model.hpp"
#include "model_part.hpp"
#include "z_ordering.hpp"
#include "log.hpp"
#include "sprite_part_index.hpp"
#include "environment.hpp"
#include "../load/model/collection.hpp"
#include "../load/model/context.hpp"
#include "../load/context.hpp"
#include "../client/id_dont_care.hpp"
#include "../exception.hpp"
#include <sge/log/parameters/inherited.hpp>
#include <sge/log/headers.hpp>
#include <sge/log/object.hpp>
#include <sge/math/vector/is_null.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/sprite/object_impl.hpp>
#include <fcppt/text.hpp>
#include <sge/make_auto_ptr.hpp>
#include <boost/foreach.hpp>
#include <ostream>

sanguis::draw::model::model(
	draw::environment const &env,
	entity_id const id,
	sge::string const &name,
	sprite::order const order,
	bool const show_healthbar,
	draw::remove_action::type const remove_action_)
:
	container(
		env,
		id,
		env.context().models()()[name].size(),
		order
	),
	attacking(false),
	reloading(false),
	health_(0),
	max_health_(0),
	healthbar_(
		show_healthbar
		?
			new healthbar(
				env
			)
		:
			0
	),
	remove_action_(remove_action_)
{
	part_vector::size_type i(0);

	BOOST_FOREACH(
		load::model::model::value_type const &p,
		env.context().models()()[name]
	)
		parts.push_back(
			new model_part(
				p.second,
				at(sprite_part_index(i++))
			)
		);
	
	change_animation(
		animation_type::deploying
	);
}

sanguis::draw::model::~model()
{}

sanguis::draw::funit
sanguis::draw::model::max_health() const
{
	return max_health_;
}

sanguis::draw::funit
sanguis::draw::model::health() const
{
	return health_;
}

void sanguis::draw::model::update(
	time_type const time)
{
	container::update(time);

	if(healthbar_)
		healthbar_->attach_to(
			master().pos(),
			master().size());

	BOOST_FOREACH(model_part &p, parts)
		p.update(time);
}

void sanguis::draw::model::orientation(
	sprite::rotation_type const rot)
{
	BOOST_FOREACH(model_part &p, parts)
		p.orientation(rot);
}

void sanguis::draw::model::orientation(
	sprite::rotation_type const rot,
	size_type const index)
{
	parts.at(index).orientation(rot);	
}

bool sanguis::draw::model::may_be_removed() const
{
	return entity::may_be_removed()
		&& animations_ended();
}

sanguis::draw::remove_action::type
sanguis::draw::model::remove_action() const
{
	return remove_action_; 
}

void sanguis::draw::model::speed(
	vector2 const &s)
{
	vector2 const old_speed(
		speed());
	
	container::speed(s);

	if(is_null(s) != is_null(old_speed))
		change_animation();
}

sanguis::draw::model_part &
sanguis::draw::model::part(
	sprite_part_index const &idx)
{
	return parts.at(idx.get());
}

bool sanguis::draw::model::dead() const
{
	return health() <= 0;
}

bool sanguis::draw::model::walking() const
{
	return !is_null(speed());
}

bool sanguis::draw::model::has_health() const
{
	return max_health() > 0;
}

void sanguis::draw::model::on_decay()
{
	/*
	if(!has_health())
		return;
	
	entity_auto_ptr blood_(
		sge::make_auto_ptr<
			blood
		>(
			environment(),
			pos()));*/
}

void sanguis::draw::model::health(
	funit const health)
{
	health_ = health;
	update_healthbar();
	
	if(!dead())
		return;
	
	healthbar_.reset();
	change_animation();
	speed(vector2::null()); // FIXME
}

void sanguis::draw::model::max_health(
	funit const max_health)
{
	max_health_ = max_health;
	update_healthbar();
}

void sanguis::draw::model::weapon(
	weapon_type::type const weapon_)
{
	BOOST_FOREACH(model_part &p, parts)
		p.weapon(weapon_);
	change_animation();
}

void sanguis::draw::model::start_attacking()
{
	if(attacking)
		SGE_LOG_WARNING(
			log(),
			sge::log::_ << FCPPT_TEXT("start_attacking(): already attacking!"));
	attacking = true;

	change_animation();
}

void sanguis::draw::model::stop_attacking()
{
	if(!attacking)
		SGE_LOG_WARNING(
			log(),
			sge::log::_ << FCPPT_TEXT("stop_attacking(): already not attacking!"));
	attacking = false;

	change_animation();
}

void sanguis::draw::model::start_reloading()
{
	if(reloading)
		SGE_LOG_WARNING(
			log(),
			sge::log::_ << FCPPT_TEXT("start_reloading(): already reloading!"));
	reloading = true;

	change_animation();
}

void sanguis::draw::model::stop_reloading()
{
	if(!reloading)
		SGE_LOG_WARNING(
			log(),
			sge::log::_ << FCPPT_TEXT("stop_reloading(): already not reloading!"));
	reloading = false;

	change_animation();
}

void sanguis::draw::model::change_animation()
{
	change_animation(
		animation());
}

void sanguis::draw::model::change_animation(
	animation_type::type const nanim)
{
	BOOST_FOREACH(model_part &p, parts)
	{
		animation_type::type part_anim(
			nanim);
		while(!p.try_animation(part_anim))
			part_anim = fallback_anim(part_anim);
	}
}

sanguis::animation_type::type
sanguis::draw::model::fallback_anim(
	animation_type::type const anim) const
{
	switch(anim) {
	case animation_type::none:
		return animation_type::size;
	case animation_type::attacking:
	case animation_type::reloading:
		return walking()
		? animation_type::walking
		: animation_type::none;
	case animation_type::deploying:
	case animation_type::walking:
	case animation_type::dying:
		return animation_type::none;
	default:
		throw exception(
			FCPPT_TEXT("Invalid animation in fallback_anim!"));
	}
}

sanguis::animation_type::type
sanguis::draw::model::animation() const
{
	return dead()
	? animation_type::dying
	: reloading
		? animation_type::reloading
		: attacking
			? animation_type::attacking
			: is_null(container::speed())
				? animation_type::none
				: animation_type::walking;
}

void sanguis::draw::model::update_healthbar()
{
	if(!healthbar_)
		return;
	
	healthbar_->update_health(
		health(),
		max_health()
	);
}

bool sanguis::draw::model::animations_ended() const
{
	BOOST_FOREACH(part_vector::const_reference part, parts)
		if(!part.animation_ended())
			return false;
	return true;
}

sge::log::object &
sanguis::draw::model::log()
{
	static sge::log::object log_(
		sge::log::parameters::inherited(
			draw::log(),
			FCPPT_TEXT("model")
		)
	);
	return log_;
}
