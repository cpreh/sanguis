#ifndef SANGUIS_SERVER_ENTITIES_IFACES_WITH_ANGLE_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_IFACES_WITH_ANGLE_HPP_INCLUDED

#include <sanguis/server/angle.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{
namespace ifaces
{

class with_angle
{
	FCPPT_NONCOPYABLE(
		with_angle
	);
protected:
	with_angle();
public:
	virtual
	sanguis::server::angle const
	angle() const = 0;

	virtual
	~with_angle();
};

}
}
}
}

#endif
