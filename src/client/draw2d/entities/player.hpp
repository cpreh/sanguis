#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_PLAYER_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_PLAYER_HPP_INCLUDED

#include "model/parameters_fwd.hpp"
#include "model/object.hpp"
#include "../sprite/rotation.hpp"
#include "../funit.hpp"
#include "../speed.hpp"
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
		sprite::rotation
	);

	void
	speed(
		draw2d::speed const &
	);
protected:
	void
	update(
		time_type
	);
private:
	using container::orientation;
	using container::speed;

	draw2d::funit angle_;
};

}
}
}
}

#endif
