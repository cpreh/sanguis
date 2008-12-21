#include "bullet.hpp"
#include "unit.hpp"
#include "z_ordering.hpp"
#include "sprite_part_index.hpp"
#include <boost/none.hpp>

namespace
{

sanguis::draw::sprite_part_index const
	tail(1);

}

sanguis::draw::bullet::bullet(
	load::context const &ctx,
	entity_id id,
	system &sys,
	sge::string const &name)
:
	model(
		ctx,
		id,
		sys,
		name,
		z_ordering::bullet,
		false),
	origin()
{
	at(tail).size().w() = static_cast<unit>(3); // TODO: which value is best here?
}

void sanguis::draw::bullet::update(
	time_type const time)
{
	if (!origin)
		origin = center();
	
	model::update(time);

	funit const
		max_tail_length =
			static_cast<funit>(160),
		tail_length = 
			std::min(
				static_cast<funit>(((*origin) - center()).length()),
				max_tail_length);

	vector2 const
		newsize(
			tail_length,
			static_cast<funit>(at(tail).size().h())),
		pos(
			sge::math::structure_cast<funit>(center())),
		newpos( 
			speed().is_null()
			? pos
			: pos - sge::math::normalize(speed())*static_cast<funit>(0.5)*newsize.length());

	at(tail).center(
		sge::math::structure_cast<sge::sprite::unit>(
			newpos));

	at(tail).w() =
		static_cast<sge::sprite::unit>(
			tail_length);
}
