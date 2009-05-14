#include "bullet.hpp"
#include "unit.hpp"
#include "z_ordering.hpp"
#include "sprite_part_index.hpp"
#include "object.hpp"
#include <sge/optional_impl.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/vector/arithmetic.hpp>
#include <sge/math/vector/is_null.hpp>
#include <sge/math/vector/normalize.hpp>
#include <sge/math/vector/length.hpp>
#include <sge/math/vector/structure_cast.hpp>

namespace
{

sanguis::draw::sprite_part_index const
	tail(1);

}

sanguis::draw::bullet::bullet(
	draw::environment const &env,
	entity_id id,
	sge::string const &name)
:
	model(
		env,
		id,
		name,
		z_ordering::bullet,
		false,
		draw::remove_action::remove),
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
				sge::math::vector::length<funit>((*origin) - center()),
				max_tail_length
			);

	vector2 const
		newsize(
			tail_length,
			static_cast<funit>(at(tail).size().h())),
		pos(
			sge::math::vector::structure_cast<
				vector2
			>(
				center())),
		newpos( 
			is_null(speed())
			? pos
			: pos - normalize(speed())*static_cast<funit>(0.5) * length(newsize));

	at(tail).center(
		sge::math::vector::structure_cast<
			sge::sprite::point
		>(
			newpos));

	at(tail).w() =
		static_cast<sge::sprite::unit>(
			tail_length);
}
