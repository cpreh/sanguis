#ifndef SANGUIS_CLIENT_DRAW2D_ENTITIES_IFACES_WITH_SPEED_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_ENTITIES_IFACES_WITH_SPEED_HPP_INCLUDED

#include <sanguis/client/draw2d/speed_fwd.hpp>
#include <fcppt/nonmovable.hpp>


namespace sanguis::client::draw2d::entities::ifaces
{

class with_speed
{
	FCPPT_NONMOVABLE(
		with_speed
	);
protected:
	with_speed();

	virtual
	~with_speed();
public:
	virtual
	void
	speed(
		sanguis::client::draw2d::speed const &
	) = 0;

	[[nodiscard]]
	virtual
	sanguis::client::draw2d::speed
	speed() const = 0;
};

}

#endif
