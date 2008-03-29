#include "bullet.hpp"
#include "resource_factory.hpp"

sanguis::draw::bullet::bullet(
	const entity_id id,
	const sge::sprite::point& pos_,
	const sge::space_unit angle,
	const sge::math::vector2& speed)
: sprite(
	id,
	pos_,
	sge::sprite_texture_dim,
	resource::texture(
		SGE_TEXT("bullet")),
	angle,
	speed,
	-3)
{}

void sanguis::draw::bullet::update(
	const time_type time)
{
	sprite::update(time);
}
