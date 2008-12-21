#ifndef SANGUIS_DRAW_PLAYER_HPP_INCLUDED
#define SANGUIS_DRAW_PLAYER_HPP_INCLUDED

#include "model.hpp"
#include "types.hpp"
#include "reaper.hpp"
#include <sge/sprite/texture_animation.hpp>
#include <sge/math/vector.hpp>

namespace sanguis
{
namespace load
{
class context;
}
namespace draw
{

class player : public model {
public:
	player(
		load::context const &,
		entity_id id,
		system &);
	void orientation(sge::sprite::rotation_type);
	void speed(vector2 const &);
private:
	using sprite::orientation;
	using sprite::speed;

	void update(time_type);
	funit  angle_,
	       target_angle;
	reaper reaper_;
};


}
}

#endif
