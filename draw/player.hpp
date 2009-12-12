#ifndef SANGUIS_DRAW_PLAYER_HPP_INCLUDED
#define SANGUIS_DRAW_PLAYER_HPP_INCLUDED

#include "environment_fwd.hpp"
#include "model.hpp"
#include "vector2.hpp"
#include "sprite/rotation_type.hpp"

namespace sanguis
{
namespace draw
{

class player : public model {
public:
	player(
		draw::environment const &,
		entity_id id);

	void orientation(
		sprite::rotation_type);
	void speed(
		vector2 const &);
private:
	using sprite::orientation;
	using sprite::speed;

	void update(time_type);

	funit
		angle_,
		target_angle;
};

}
}

#endif
