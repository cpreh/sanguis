#ifndef SANGUIS_SERVER_ENTITIES_WITH_VELOCITY_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_VELOCITY_HPP_INCLUDED

#include <sanguis/collision/speed_fwd.hpp>
#include <sanguis/server/direction.hpp>
#include <sanguis/server/optional_mass_fwd.hpp>
#include <sanguis/server/radius_fwd.hpp>
#include <sanguis/server/speed_fwd.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/movement_speed_fwd.hpp>
#include <sanguis/server/entities/movement_speed_initial_fwd.hpp>
#include <sanguis/server/entities/optional_transfer_result_fwd.hpp>
#include <sanguis/server/entities/transfer_parameters_fwd.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/with_velocity_fwd.hpp>
#include <sanguis/server/entities/ifaces/with_id.hpp>
#include <sanguis/server/entities/ifaces/with_velocity.hpp>
#include <sanguis/server/entities/property/changeable.hpp>
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
		sanguis::server::radius,
		sanguis::server::optional_mass const &,
		sanguis::server::entities::movement_speed_initial,
		sanguis::server::direction
	);

	void
	update()
	override;

	sanguis::server::entities::optional_transfer_result
	on_transfer(
		sanguis::server::entities::transfer_parameters const &
	)
	override;
public:
	~with_velocity()
	override;

	sanguis::server::entities::property::changeable &
	movement_speed()
	override;

	sanguis::server::entities::movement_speed const
	max_movement_speed() const;

	sanguis::server::direction const
	direction() const;

	sanguis::server::speed const
	speed() const
	override;

	void
	direction(
		sanguis::server::direction
	)
	override;
private:
	void
	desired_speed_change();

	void
	speed_changed(
		sanguis::collision::speed
	)
	override;

	sanguis::server::speed const
	desired_speed() const;

	sanguis::server::speed const
	initial_speed() const
	override;

	sanguis::server::entities::property::changeable movement_speed_;

	sanguis::server::direction direction_;

	sanguis::server::net::speed net_speed_;

	fcppt::signal::scoped_connection const speed_change_;
};

}
}
}

#endif

