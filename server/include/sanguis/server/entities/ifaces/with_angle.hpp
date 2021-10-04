#ifndef SANGUIS_SERVER_ENTITIES_IFACES_WITH_ANGLE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_IFACES_WITH_ANGLE_HPP_INCLUDED

#include <sanguis/server/angle_fwd.hpp>
#include <fcppt/nonmovable.hpp>


namespace sanguis::server::entities::ifaces
{

class with_angle
{
	FCPPT_NONMOVABLE(
		with_angle
	);
protected:
	with_angle();
public:
	[[nodiscard]]
	virtual
	sanguis::server::angle
	angle() const = 0;

	virtual
	void
	angle(
		sanguis::server::angle
	) = 0;

	virtual
	~with_angle();
};

}

#endif
