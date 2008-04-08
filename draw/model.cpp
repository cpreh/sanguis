#include "model.hpp"
#include "../load/model/collection.hpp"
#include "../load/model/singleton.hpp"
#include "../client/id_dont_care.hpp"
#include <boost/foreach.hpp>

sanguis::draw::model::model(
	const entity_id id,
	sge::string const& name)
: sprite(
	id,
	load::model::singleton()[name].size())
{
	part_vector::size_type i(0);
	BOOST_FOREACH(
		load::model::model::value_type const& p,
		load::model::singleton()[name])
	{
		parts.push_back(
			model_part(
				p.second,
				at(i++)));
	}
}

void sanguis::draw::model::update(
	const time_type time)
{
	sprite::update(time);

	BOOST_FOREACH(model_part &p, parts)
	{
		p.animation(
			speed().is_null()
			? animation_type::none
			: animation_type::walking);
		p.update();
	}
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
