#ifndef SANGUIS_SERVER_ENTITIES_IFACES_WITH_VELOCITY_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_IFACES_WITH_VELOCITY_HPP_INCLUDED

#include <sanguis/server/speed_fwd.hpp>
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

	virtual
	void
	on_speed_change(
		sanguis::server::speed const &
	);

	virtual
	sanguis::server::speed const
	initial_abs_speed() const = 0;

	virtual
	sanguis::server::speed const
	actual_speed() const = 0;
public:
	virtual
	~with_velocity() = 0;
};

}
}
}
}

#endif
