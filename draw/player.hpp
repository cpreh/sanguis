#ifndef SANGUIS_DRAW_PLAYER_HPP_INCLUDED
#define SANGUIS_DRAW_PLAYER_HPP_INCLUDED

#include "model.hpp"
#include "types.hpp"
#include "reaper.hpp"
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
	void speed(sge::math::vector2 const &);
private:
	void update(time_type);
	sge::space_unit angle_,
	                target_angle;
	reaper          reaper_;
};


}
}

#endif
