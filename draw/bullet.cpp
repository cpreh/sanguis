#include "bullet.hpp"
#include "z_ordering.hpp"
#include "sprite_part_index.hpp"
#include <boost/none.hpp>

namespace
{

sanguis::draw::sprite_part_index const
	tail(1);

}

sanguis::draw::bullet::bullet(
	entity_id id,
	system &sys,
	sge::string const &name)
: model(
	id,
	sys,
	name,
	z_ordering::bullet,
	false),
  origin()
{
	at(tail).size().w() = static_cast<sge::sprite::unit>(3); // TODO: which value is best here?
}

void sanguis::draw::bullet::update(const time_type time)
{
	if (!origin)
		origin = center();
	
	model::update(time);

	sge::space_unit const
		max_tail_length =
			static_cast<sge::space_unit>(160),
		tail_length = 
			std::min(
				static_cast<sge::space_unit>(((*origin) - center()).length()),
				max_tail_length);

	sge::math::vector2 const
		newsize(
			tail_length,
			sge::su(at(tail).size().h())),
		pos(
			sge::math::structure_cast<sge::space_unit>(center())),
		newpos( 
			speed().is_null()
			? pos
			: pos - sge::math::normalize(speed())*sge::su(0.5)*newsize.length());

	at(tail).set_center(
		sge::math::structure_cast<sge::sprite::unit>(
			newpos));

	at(tail).w() =
		static_cast<sge::sprite::unit>(
			tail_length);
}
