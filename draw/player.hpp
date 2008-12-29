#ifndef SANGUIS_DRAW_PLAYER_HPP_INCLUDED
#define SANGUIS_DRAW_PLAYER_HPP_INCLUDED

#include "model.hpp"
#include "reaper.hpp"
#include "vector2.hpp"
#include <sge/sprite/texture_animation.hpp>

namespace sanguis
{
namespace draw
{

class environment;

class player : public model {
public:
	player(
		draw::environment const &,
		entity_id id);

	void orientation(
		sge::sprite::rotation_type);
	void speed(
		vector2 const &);
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
