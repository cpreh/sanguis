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
	-3),
	tail_length(static_cast<sge::space_unit>(0))
{
	add_sprite(
		sge::sprite(pos_,sge::virtual_texture_ptr(),sge::sprite_dim(1,1),sge::colors::white,-3,angle));
	
	at(1).rotate_around(sge::sprite_point(static_cast<sge::sprite_unit>(0),static_cast<sge::sprite_unit>(0)));
}

void sanguis::draw::bullet::update(const time_type time)
{
	sprite::update(time);

	//const sge::space_unit max_tail_length = static_cast<sge::space_unit>(20);

	//tail_length = std::min(max_tail_length,tail_length + sge::su(50) * time);
	tail_length += sge::su(50) * time;

	at(1).size() = sge::sprite_dim(at(1).size().w(),static_cast<sge::sprite_unit>(tail_length));
}
