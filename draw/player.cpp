#include <sge/string.hpp>
#include "player.hpp"
#include "resource_factory.hpp"

sanguis::draw::player::player(
	const entity_id id,
	const sge::sprite::point& pos_,
	const sge::sprite::dim& sz,
	const sge::space_unit angle,
	const sge::math::vector2& speed)
: sprite(
	id,
	speed),
  walk_animation(
  	resource::animation(
		SGE_TEXT("player_walk")))
{
	pos(pos_);
	sge::sprite skel_sprite(
		sge::sprite(
			pos_,
			resource::texture(SGE_TEXT("player_up")),
			sz,
			sge::colors::white,
			1,
			angle));
	add_sprite(skel_sprite);

	skel_sprite.z() = static_cast<sge::space_unit>(0);
	add_sprite(skel_sprite);

	walk_animation.bind(&bottom_sprite());
}

void sanguis::draw::player::orientation(sge::space_unit u)
{
	up_sprite().rotation(u);
}

void sanguis::draw::player::update(const time_type time)
{
	sprite::update(time);
	if(!speed().is_null())
		walk_animation.process();
	// TODO
	//	bottom_sprite().rotation(sge::math::angle_to(sge::math::vector2(),speed()));
}

sge::sprite& sanguis::draw::player::bottom_sprite()
{
	return at(0);
}

sge::sprite& sanguis::draw::player::up_sprite()
{
	return at(1);
}
