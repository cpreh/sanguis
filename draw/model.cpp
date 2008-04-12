#include "model.hpp"
#include "../load/model/collection.hpp"
#include "../load/model/singleton.hpp"
#include "../client/id_dont_care.hpp"
#include <sge/iostream.hpp>
#include <boost/foreach.hpp>
#include <ostream>

sanguis::draw::model::model(
	const entity_id id,
	sge::string const& name)
: sprite(
	id,
	load::model::singleton()[name].size()),
  attacking(false)
{
	part_vector::size_type i(0);
	BOOST_FOREACH(
		load::model::model::value_type const& p,
		load::model::singleton()[name])
		parts.push_back(
			model_part(
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
		p.update();
	}
}

sanguis::draw::entity::sprite_vector
sanguis::draw::model::to_sprites() const
{
	sprite_vector sprites(sprite::to_sprites());
	sprite_vector const& healthbar_sprites(healthbar_.to_sprites());
	sprites.insert(sprites.end(), healthbar_sprites.begin(), healthbar_sprites.end());
	return sprites;
}

void sanguis::draw::model::health(
	const sge::space_unit health)
{
	healthbar_.health(health);
	/*if(sge::math::almost_zero(health))
		BOOST_FOREACH(model_part &p, parts)
			p.animation(
				animation_type::dying);*/
}

void sanguis::draw::model::max_health(
	const sge::space_unit max_health)
{
	healthbar_.max_health(max_health);
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
	return sge::math::almost_zero(healthbar_.health())
	? animation_type::dying
	: attacking
		? animation_type::attacking
		: speed().is_null()
			? animation_type::none
			: animation_type::walking;
}
