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
#include <fcppt/nonmovable.hpp>
#include <fcppt/signal/auto_connection.hpp>


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
	FCPPT_NONMOVABLE(
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

	[[nodiscard]]
	sanguis::server::entities::optional_transfer_result
	on_transfer(
		sanguis::server::entities::transfer_parameters const &
	)
	override;
public:
	~with_velocity()
	override;

	[[nodiscard]]
	sanguis::server::entities::property::changeable &
	movement_speed()
	override;

	[[nodiscard]]
	sanguis::server::entities::movement_speed
	max_movement_speed() const;

	[[nodiscard]]
	sanguis::server::direction
	direction() const;

	[[nodiscard]]
	sanguis::server::speed
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
		sanguis::collision::speed const &
	)
	override;

	[[nodiscard]]
	sanguis::server::speed
	desired_speed() const;

	[[nodiscard]]
	sanguis::server::speed
	initial_speed() const
	override;

	sanguis::server::entities::property::changeable movement_speed_;

	sanguis::server::direction direction_;

	sanguis::server::net::speed net_speed_;

	fcppt::signal::auto_connection const speed_change_;
};

}
}
}

#endif

