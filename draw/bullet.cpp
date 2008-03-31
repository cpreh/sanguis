#include "bullet.hpp"
#include "resource_factory.hpp"
#include "z_ordering.hpp"

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
	z_ordering::bullet),
	origin(pos_)
{
	add_sprite(
		sge::sprite(pos_,
			resource::texture(SGE_TEXT("tail")),sge::sprite_texture_dim,sge::colors::white,z_ordering::bullet,angle));
	
	at(1).size().w() = static_cast<sge::sprite_unit>(1);
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

	at(1).set_center(sge::math::structure_cast<sge::sprite_unit>(newpos));

	at(1).size() = sge::sprite_dim(static_cast<sge::sprite_unit>(newsize.x()),static_cast<sge::sprite_unit>(newsize.y()));
}
