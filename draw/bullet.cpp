#include "bullet.hpp"
#include "z_ordering.hpp"
#include "../load/resource_factory.hpp"
#include <boost/none.hpp>

sanguis::draw::bullet::bullet(
	const entity_id id)
: sprite(
	id,
	2),
  origin()
{
	at(0) = sge::sprite::object(
		boost::none,
		load::resource::texture(
			SGE_TEXT("bullet")),
		sge::sprite::texture_dim,
		boost::none,
		z_ordering::bullet);

	at(1) = sge::sprite::object(
		boost::none,
		load::resource::texture(SGE_TEXT("tail")),
		sge::sprite::texture_dim,
		boost::none,
		z_ordering::bullet);
	
	at(1).size().w() = static_cast<sge::sprite::unit>(1);
}

void sanguis::draw::bullet::update(const time_type time)
{
	sprite::update(time);

	const sge::space_unit max_tail_length = static_cast<sge::space_unit>(160);
	const sge::space_unit tail_length = 
		std::min(static_cast<sge::space_unit>((origin - center()).length()),max_tail_length);

	const sge::math::vector2 newsize(tail_length,sge::su(at(1).size().h()));
	const sge::math::vector2 pos = sge::math::structure_cast<sge::space_unit>(center());

	const sge::math::vector2 newpos = pos - sge::math::normalize(speed())*sge::su(0.5)*newsize.length();

	at(1).set_center(sge::math::structure_cast<sge::sprite::unit>(newpos));

	at(1).size() = sge::sprite::dim(static_cast<sge::sprite::unit>(newsize.x()),static_cast<sge::sprite::unit>(newsize.y()));
}
