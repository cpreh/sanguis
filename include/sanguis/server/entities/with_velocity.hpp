#ifndef SANGUIS_SERVER_ENTITIES_WITH_VELOCITY_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_VELOCITY_HPP_INCLUDED

#include <sanguis/server/direction.hpp>
#include <sanguis/server/speed_fwd.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/with_velocity_fwd.hpp>
#include <sanguis/server/entities/ifaces/with_id.hpp>
#include <sanguis/server/entities/ifaces/with_velocity.hpp>
#include <sanguis/server/entities/property/changeable.hpp>
#include <sanguis/server/entities/property/initial_fwd.hpp>
#include <sanguis/server/entities/property/value.hpp>
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
	public virtual sanguis::server::entities::base,
	public virtual sanguis::server::entities::ifaces::with_id,
	protected virtual sanguis::server::entities::ifaces::with_velocity
{
	FCPPT_NONCOPYABLE(
		with_velocity
	);
protected:
	with_velocity(
		sanguis::server::entities::property::initial const &speed,
		sanguis::server::direction
	);
public:
	virtual
	~with_velocity();

	sanguis::server::entities::property::changeable &
	movement_speed();

	sanguis::server::direction const
	direction() const;

	sanguis::server::speed const
	speed() const;

	void
	speed(
		sanguis::server::speed
	);

	void
	direction(
		sanguis::server::direction
	);
private:
	void
	speed_change(
		sanguis::server::entities::property::value
	);

	sanguis::server::speed const
	initial_abs_speed() const;

	sanguis::server::entities::property::changeable movement_speed_;

	sanguis::server::direction direction_;

	fcppt::signal::scoped_connection const speed_change_;
};

}
}
}

#endif

