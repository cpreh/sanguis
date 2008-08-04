#include "model.hpp"
#include "z_ordering.hpp"
#include "../load/model/collection.hpp"
#include "../load/model/singleton.hpp"
#include "../client/id_dont_care.hpp"
#include <sge/iostream.hpp>
#include <boost/foreach.hpp>
#include <ostream>

sanguis::draw::model::model(
	entity_id const id,
	system &sys,
	sge::string const &name,
	object::order_type const order)
: sprite(
	id,
	sys,
	load::model::singleton()[name].size(),
	order),
  attacking(false),
  healthbar_(sys)
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

void sanguis::draw::model::update(
	const time_type time)
{
	sprite::update(time);
	healthbar_.attach_to(
		master().pos(),
		master().size());

	BOOST_FOREACH(model_part &p, parts)
	{
		p.animation(animation());
		p.update(time);
	}

	// TODO: fix this
	if(healthbar_.dead())
		speed(sge::math::vector2(0,0));
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
	healthbar_.health(health);
}

void sanguis::draw::model::max_health(
	const sge::space_unit max_health)
{
	healthbar_.max_health(max_health);
}

sge::space_unit sanguis::draw::model::max_health() const
{
	return healthbar_.max_health();
}

sge::space_unit sanguis::draw::model::health() const
{
	return healthbar_.health();
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
		sge::clog << SGE_TEXT("warning: model::start_attacking(): already attacking!\n");
	attacking = true;
}

void sanguis::draw::model::stop_attacking()
{
	if(!attacking)
		sge::clog << SGE_TEXT("warning: model::stop_attacking(): already not attacking!\n");
	attacking = false;
}

sanguis::animation_type::type
sanguis::draw::model::animation() const
{
	return healthbar_.dead()
	? animation_type::dying
	: attacking
		? animation_type::attacking
		: speed().is_null()
			? animation_type::none
			: animation_type::walking;
}
