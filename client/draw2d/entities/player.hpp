#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_PLAYER_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_PLAYER_HPP_INCLUDED

#include "model/parameters_fwd.hpp"
#include "model/object.hpp"
#include "../sprite/rotation_type.hpp"
#include "../vector2.hpp"
#include "../funit.hpp"
#include "../../../time_type.hpp"

namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{

class player
:
	public model::object
{
public:
	explicit player(
		model::parameters const &
	);

	void
	orientation(
		sprite::rotation_type
	);

	void
	speed(
		vector2 const &
	);
private:
	using container::orientation;
	using container::speed;

	void
	update(
		time_type
	);

	funit
		angle_,
		target_angle;
};

}
}
}
}

#endif
