#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_PLAYER_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_PLAYER_HPP_INCLUDED

#include "model/parameters_fwd.hpp"
#include "model/object.hpp"
#include "../sprite/rotation_type.hpp"
#include "../vector2.hpp"
#include "../funit.hpp"
#include "../../../time_type.hpp"
#include <fcppt/noncopyable.hpp>

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
	FCPPT_NONCOPYABLE(
		player
	);
public:
	explicit player(
		model::parameters const &
	);

	~player();

	void
	orientation(
		sprite::rotation_type
	);

	void
	speed(
		vector2 const &
	);
protected:
	void
	update(
		time_type
	);
private:
	using container::orientation;
	using container::speed;

	funit
		angle_,
		target_angle;
};

}
}
}
}

#endif
