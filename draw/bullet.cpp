#include "bullet.hpp"

sanguis::draw::bullet::bullet(
	const entity_id id,
	const sge::sprite::point& pos_,
	const sge::space_unit angle,
	const sge::math::vector2& speed)
: sprite(
	id,
	speed)
{
}

void sanguis::draw::bullet::update(
	const time_type time)
{
	sprite::update(time);
}
