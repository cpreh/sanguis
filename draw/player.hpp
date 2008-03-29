#ifndef SANGUIS_DRAW_PLAYER_HPP_INCLUDED
#define SANGUIS_DRAW_PLAYER_HPP_INCLUDED

#include <sge/sprite/texture_animation.hpp>
#include <sge/math/vector.hpp>
#include <sge/console/console.hpp>
#include "sprite.hpp"

namespace sanguis
{
namespace draw
{

class player : public sprite {
public:
	player(
		entity_id id,
		const sge::sprite::point& pos,
		sge::space_unit angle,
		const sge::math::vector2& speed);
	void orientation(sge::space_unit);
	void speed(const sge::math::vector2 &);
private:
	void update(time_type);
	sge::sprite& bottom_sprite();
	sge::sprite& top_sprite();
	sge::sprite_texture_animation walk_animation;
	sge::space_unit angle_,target_angle;
	sge::con::var<sge::space_unit> turning_speed;
};


}
}

#endif
