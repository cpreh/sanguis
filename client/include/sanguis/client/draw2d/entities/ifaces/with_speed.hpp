#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_IFACES_WITH_SPEED_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_IFACES_WITH_SPEED_HPP_INCLUDED

#include <sanguis/client/draw2d/speed_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace entities
{
namespace ifaces
{

class with_speed
{
	FCPPT_NONCOPYABLE(
		with_speed
	);
protected:
	with_speed();

	virtual
	~with_speed() = 0;
public:
	virtual
	void
	speed(
		sanguis::client::draw2d::speed const &
	) = 0;

	virtual
	sanguis::client::draw2d::speed
	speed() const = 0;
};

}
}
}
}
}

#endif
