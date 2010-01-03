#include "bullet.hpp"
#include "unit.hpp"
#include "z_ordering.hpp"
#include "sprite_part_index.hpp"
#include <sge/sprite/object_impl.hpp>
#include <sge/sprite/center.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/is_null.hpp>
#include <fcppt/math/vector/normalize.hpp>
#include <fcppt/math/vector/length.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/optional_impl.hpp>

namespace
{

sanguis::draw::sprite_part_index const
	tail(1);

}

sanguis::draw::bullet::bullet(
	draw::environment const &env,
	entity_id id,
	fcppt::string const &name)
:
	model(
		env,
		id,
		name,
		z_ordering::bullet,
		false,
		draw::remove_action::remove
	),
	origin()
{
	at(tail).w(
		static_cast<unit>(3)
	); // TODO: which value is best here?
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
				fcppt::math::vector::length<funit>((*origin) - center()),
				max_tail_length
			);

	vector2 const
		newsize(
			tail_length,
			static_cast<funit>(at(tail).size().h())
		),
		pos(
			fcppt::math::vector::structure_cast<
				vector2
			>(
				center()
			)
		),
		newpos( 
			is_null(speed())
			? pos
			: pos - normalize(speed())*static_cast<funit>(0.5) * length(newsize));

	sge::sprite::center(
		at(tail),
		fcppt::math::vector::structure_cast<
			sprite::point
		>(
			newpos
		)
	);

	at(tail).w(
		static_cast<sprite::unit>(
			tail_length
		)
	);
}