#include "model.hpp"
#include "../load/model/collection.hpp"
#include "../client/id_dont_care.hpp"
#include <boost/foreach.hpp>

sanguis::draw::model::model(
	const entity_id id,
	sge::string const& name,
	sge::sprite::point const& pos,
	sge::sprite::dim const& dim,
	const sge::sprite::rotation_type angle,
	sge::math::vector2 const& speed,
	const sge::space_unit health,
	const sge::space_unit max_health)
: sprite(
	id,
	speed,
	load::model::singleton()[name].size()),
healthbar_(
  	client::id_dont_care(),	
	sge::sprite::point(),
	sge::sprite::dim(),
//	sge::sprite::point(master().x(), master().y() - healthbar_height),
//	sge::sprite::dim(master().w(), healthbar_height),
  	health,
	max_health)

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
