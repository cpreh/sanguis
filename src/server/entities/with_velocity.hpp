#ifndef SANGUIS_SERVER_ENTITIES_WITH_VELOCITY_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_VELOCITY_HPP_INCLUDED

#include "with_velocity_fwd.hpp"
#include "base.hpp"
#include "ifaces/with_velocity.hpp"
#include "property/initial_fwd.hpp"
#include "property/changeable.hpp"
#include "property/value.hpp"
#include "../direction.hpp"
#include "../speed.hpp"
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace entities
{

class with_velocity
:
	public virtual entities::base,
	protected virtual ifaces::with_velocity
{
	FCPPT_NONCOPYABLE(
		with_velocity
	);
public:
	property::changeable &
	movement_speed();

	server::direction const
	direction() const;

	void
	direction(
		server::direction
	);

	server::speed const
	abs_speed() const;

	virtual ~with_velocity();
protected:
	with_velocity(
		property::initial const &speed,
		server::direction
	);
private:
	void
	speed_change(
		property::value
	);

	server::speed const
	initial_abs_speed() const;

	property::changeable movement_speed_;

	server::direction direction_;

	fcppt::signal::scoped_connection const speed_change_;
};

}
}
}

#endif

