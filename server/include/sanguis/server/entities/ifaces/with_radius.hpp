#ifndef SANGUIS_SERVER_ENTITIES_IFACES_WITH_RADIUS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_IFACES_WITH_RADIUS_HPP_INCLUDED

#include <sanguis/server/radius_fwd.hpp>
#include <fcppt/nonmovable.hpp>


namespace sanguis::server::entities::ifaces
{

class with_radius
{
	FCPPT_NONMOVABLE(
		with_radius
	);
protected:
	with_radius();
public:
	[[nodiscard]]
	virtual
	sanguis::server::radius
	radius() const = 0;

	virtual
	~with_radius();
};

}

#endif
