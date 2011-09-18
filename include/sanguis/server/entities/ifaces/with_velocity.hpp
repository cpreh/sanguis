#ifndef SANGUIS_SERVER_ENTITIES_IFACES_WITH_VELOCITY_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_IFACES_WITH_VELOCITY_HPP_INCLUDED

#include <sanguis/server/speed.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{
namespace ifaces
{

class with_velocity
{
	FCPPT_NONCOPYABLE(
		with_velocity
	);
protected:
	with_velocity();

	virtual void
	on_speed_change(
		server::speed const &
	);

	virtual server::speed const
	initial_abs_speed() const = 0;
public:
	virtual ~with_velocity();
};

}
}
}
}

#endif
