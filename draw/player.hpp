#ifndef SANGUIS_DRAW_PLAYER_HPP_INCLUDED
#define SANGUIS_DRAW_PLAYER_HPP_INCLUDED

#include "model.hpp"
#include "types.hpp"
#include <sge/sprite/texture_animation.hpp>
#include <sge/math/vector.hpp>

namespace sanguis
{
namespace draw
{

class player : public model {
public:
	player(
		entity_id id,
		system &);
	void orientation(sge::sprite::rotation_type);
	void speed(const sge::math::vector2 &);
	sge::space_unit health() const;
	sge::space_unit max_health() const;
	sge::sprite::point pos() const;
private:
	void update(time_type);
	object& bottom_sprite();
	object& top_sprite();
	sge::space_unit angle_,
	                target_angle;
};


}
}

#endif
