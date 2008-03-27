#ifndef DRAW_PLAYER_HPP_INCLUDED
#define DRAW_PLAYER_HPP_INCLUDED

#include <sge/sprite/texture_animation.hpp>
#include "sprite.hpp"

namespace sanguis
{
namespace draw
{

class player : public sprite {
public:
	player(entity_id id,
	       const sge::sprite::point& pos,
	       const sge::sprite::dim& sz,
	       sge::space_unit angle,
	       const sge::math::vector2& speed);
	void orientation(sge::space_unit);
private:
	void update(time_type);
	sge::sprite& bottom_sprite();
	sge::sprite& up_sprite();
	sge::sprite_texture_animation walk_animation;
};


}
}

#endif
