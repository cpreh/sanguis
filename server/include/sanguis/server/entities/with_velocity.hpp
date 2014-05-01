#ifndef SANGUIS_SERVER_ENTITIES_WITH_VELOCITY_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_VELOCITY_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/creator/grid_fwd.hpp>
#include <sanguis/server/dim_fwd.hpp>
#include <sanguis/server/direction.hpp>
#include <sanguis/server/speed_fwd.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/transfer_parameters_fwd.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/with_velocity_fwd.hpp>
#include <sanguis/server/entities/ifaces/with_id.hpp>
#include <sanguis/server/entities/ifaces/with_velocity.hpp>
#include <sanguis/server/entities/property/changeable.hpp>
#include <sanguis/server/entities/property/initial_fwd.hpp>
#include <sanguis/server/net/center.hpp>
#include <sanguis/server/net/speed.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/scoped_connection.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{

class with_velocity
:
	public virtual sanguis::server::entities::ifaces::with_id,
	public virtual sanguis::server::entities::ifaces::with_velocity,
	public sanguis::server::entities::with_body
{
	FCPPT_NONCOPYABLE(
		with_velocity
	);
protected:
	with_velocity(
		sanguis::server::dim,
		sanguis::server::entities::property::initial const &speed,
		sanguis::server::direction
	);

	virtual
	void
	update()
	override;

	bool
	on_transfer(
		sanguis::server::entities::transfer_parameters const &
	)
	override;
public:
	virtual
	~with_velocity();

	void
	world_collision(
		sanguis::creator::grid const &,
		sanguis::duration
	)
	override;

	sanguis::server::entities::property::changeable &
	movement_speed();

	sanguis::server::direction const
	direction() const;

	sanguis::server::speed const
	speed() const
	override;

	void
	direction(
		sanguis::server::direction
	);
private:
	void
	desired_speed_change();

	void
	on_position_change(
		sanguis::server::center
	)
	override;

	void
	on_speed_change(
		sanguis::server::speed
	)
	override;

	sanguis::server::speed const
	desired_speed() const;

	sanguis::server::speed const
	initial_speed() const
	override;

	sanguis::server::entities::property::changeable movement_speed_;

	sanguis::server::direction direction_;

	sanguis::server::net::center net_center_;

	sanguis::server::net::speed net_speed_;

	fcppt::signal::scoped_connection const speed_change_;
};

}
}
}

#endif

