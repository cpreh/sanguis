#ifndef SANGUIS_DRAW_PLAYER_HPP_INCLUDED
#define SANGUIS_DRAW_PLAYER_HPP_INCLUDED

#include "model.hpp"
#include <sge/sprite/texture_animation.hpp>
#include <sge/math/vector.hpp>
#include <sge/console/console.hpp>

namespace sanguis
{
namespace draw
{

class player : public model {
public:
	player(entity_id id);
	void orientation(sge::space_unit);
	void speed(const sge::math::vector2 &);
private:
	void update(time_type);
	sge::sprite::object& bottom_sprite();
	sge::sprite::object& top_sprite();
	sge::sprite::texture_animation walk_animation;
	sge::space_unit angle_,
	                target_angle;
	sge::con::var<sge::space_unit> turning_speed;
	sge::space_unit health_;
};


}
}

#endif
