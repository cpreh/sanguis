#include "model.hpp"
#include "z_ordering.hpp"
#include "log.hpp"
#include "../log_headers.hpp"
#include "../load/model/collection.hpp"
#include "../load/model/singleton.hpp"
#include "../client/id_dont_care.hpp"
#include <sge/log/logger.hpp>
#include <sge/text.hpp>
#include <boost/foreach.hpp>
#include <ostream>

sanguis::draw::model::model(
	entity_id const id,
	system &sys,
	sge::string const &name,
	object::order_type const order,
	bool const show_healthbar,
	sge::space_unit const start_health)
: sprite(
	id,
	sys,
	load::model::singleton()[name].size(),
	order),
  attacking(false),
  reloading(false),
  health_(start_health),
  max_health_(start_health),
  healthbar_(
	show_healthbar
	? new healthbar(
		sys)
	: 0)
{
	part_vector::size_type i(0);
	BOOST_FOREACH(
		load::model::model::value_type const& p,
		load::model::singleton()[name])
			parts.push_back(
			new model_part(
				p.second,
				at(i++)));
}

sge::space_unit
sanguis::draw::model::max_health() const
{
	return max_health_;
}

sge::space_unit
sanguis::draw::model::health() const
{
	return health_;
}

void sanguis::draw::model::update(
	time_type const time)
{
	sprite::update(time);

	if(healthbar_)
		healthbar_->attach_to(
			master().pos(),
			master().size());

	BOOST_FOREACH(model_part &p, parts)
	{
		p.animation(animation());
		p.update(time);
	}

	// TODO: fix this
	if(dead())
	{
		healthbar_.reset();
		speed(sge::math::vector2(0,0));
	}
}

void sanguis::draw::model::orientation(
	const sge::sprite::rotation_type rot)
{
	BOOST_FOREACH(model_part &p, parts)
		p.orientation(rot);
}

void sanguis::draw::model::orientation(
	const sge::sprite::rotation_type rot,
	const sprite_vector::size_type index)
{
	parts.at(index).orientation(rot);	
}

void sanguis::draw::model::health(
	const sge::space_unit health)
{
	health_ = health;
	update_healthbar();
}

void sanguis::draw::model::max_health(
	const sge::space_unit max_health)
{
	max_health_ = max_health;
	update_healthbar();
}

void sanguis::draw::model::weapon(
	const weapon_type::type weapon_)
{
	BOOST_FOREACH(model_part &p, parts)
		p.weapon(weapon_);
}

void sanguis::draw::model::start_attacking()
{
	if(attacking)
		SGE_LOG_WARNING(
			log(),
			sge::log::_1 << SGE_TEXT("model::start_attacking(): already attacking!"));
	attacking = true;
}

void sanguis::draw::model::stop_attacking()
{
	if(!attacking)
		SGE_LOG_WARNING(
			log(),
			sge::log::_1 << SGE_TEXT("model::stop_attacking(): already not attacking!"));
	attacking = false;
}

void sanguis::draw::model::start_reloading()
{
	if(reloading)
		SGE_LOG_WARNING(
			log(),
			sge::log::_1 << SGE_TEXT("model::start_reloading(): already reloading!"));
	reloading = true;
}

void sanguis::draw::model::stop_reloading()
{
	if(!reloading)
		SGE_LOG_WARNING(
			log(),
			sge::log::_1 << SGE_TEXT("model::stop_reloading(): already not reloading!"));
	reloading = false;
}

sanguis::animation_type::type
sanguis::draw::model::animation() const
{
	// deploying should be handled in model_part
	// because the start of the animation type is set to it
	return dead()
	? animation_type::dying
	: reloading
		? animation_type::reloading
		: attacking
			? animation_type::attacking
			: speed().is_null()
				? animation_type::none
				: animation_type::walking;
}

bool sanguis::draw::model::dead() const
{
	return health() <= 0;
}

void sanguis::draw::model::update_healthbar()
{
	if(!healthbar_)
		return;
	healthbar_->health(health());
	healthbar_->max_health(max_health());
}

sge::log::logger &
sanguis::draw::model::log()
{
	static sge::log::logger log_(
		draw::log(),
		SGE_TEXT("model: "));
	return log_;
}
