#ifndef SANGUIS_SERVER_ENTITIES_IFACES_WITH_RADIUS_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_IFACES_WITH_RADIUS_HPP_INCLUDED

#include <sanguis/server/radius_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{
namespace ifaces
{

class with_radius
{
	FCPPT_NONCOPYABLE(
		with_radius
	);
protected:
	with_radius();
public:
	virtual
	sanguis::server::radius
	radius() const = 0;

	virtual
	~with_radius() = 0;
};

}
}
}
}

#endif
