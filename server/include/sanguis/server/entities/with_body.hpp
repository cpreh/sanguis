#ifndef SANGUIS_SERVER_ENTITIES_WITH_BODY_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_BODY_HPP_INCLUDED

#include <sanguis/collision/center_fwd.hpp>
#include <sanguis/collision/speed_fwd.hpp>
#include <sanguis/collision/world/body_base.hpp>
#include <sanguis/collision/world/body_group_fwd.hpp>
#include <sanguis/server/angle.hpp>
#include <sanguis/server/center_fwd.hpp>
#include <sanguis/server/optional_mass_fwd.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/speed_fwd.hpp>
#include <sanguis/server/collision/body.hpp>
#include <sanguis/server/collision/body_fwd.hpp>
#include <sanguis/server/entities/optional_transfer_result_fwd.hpp>
#include <sanguis/server/entities/remove_from_world_result_fwd.hpp>
#include <sanguis/server/entities/transfer_parameters_fwd.hpp>
#include <sanguis/server/entities/with_body_fwd.hpp>
#include <sanguis/server/entities/with_ghosts.hpp>
#include <sanguis/server/entities/ifaces/with_angle.hpp>
#include <sanguis/server/entities/ifaces/with_id.hpp>
#include <sanguis/server/entities/ifaces/with_links.hpp>
#include <sanguis/server/entities/ifaces/with_radius.hpp>
#include <sanguis/server/net/angle.hpp>
#include <sanguis/server/net/center.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/logic/tribool_fwd.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace entities
{

class with_body
:
	public virtual sanguis::server::entities::with_ghosts,
	public virtual sanguis::server::entities::ifaces::with_angle,
	public virtual sanguis::server::entities::ifaces::with_id,
	public virtual sanguis::server::entities::ifaces::with_links,
	public virtual sanguis::server::entities::ifaces::with_radius,
	public sanguis::collision::world::body_base
{
	FCPPT_NONMOVABLE(
		with_body
	);
public:
	with_body(
		sanguis::server::radius,
		sanguis::server::optional_mass const &
	);

	~with_body()
	override;

	// entities::base overridden functions
	[[nodiscard]]
	sanguis::server::center
	center() const
	override;

	// ifaces::with_angle overridden functions
	[[nodiscard]]
	sanguis::server::angle
	angle() const
	override;

	// own functions
	void
	center(
		sanguis::server::center const &
	);

	void
	angle(
		sanguis::server::angle
	)
	override;

	[[nodiscard]]
	sanguis::server::radius
	radius() const
	override;

	[[nodiscard]]
	sanguis::server::entities::remove_from_world_result
	remove_from_world()
	override;
protected:
	// entities::base::on_transfer
	[[nodiscard]]
	sanguis::server::entities::optional_transfer_result
	on_transfer(
		sanguis::server::entities::transfer_parameters const &
	)
	override;

	void
	update()
	override;

	void
	body_speed(
		sanguis::server::speed const &
	);

	[[nodiscard]]
	sanguis::server::speed
	body_speed() const;
private:
	// collision::body_base
	[[nodiscard]]
	boost::logic::tribool
	can_collide_with(
		sanguis::collision::world::body_base const &
	) const
	override;

	void
	collision(
		sanguis::collision::world::body_base & // NOLINT(google-runtime-references)
	) // NOLINT(google-runtime-references)
	override;

	[[nodiscard]]
	virtual
	boost::logic::tribool
	can_collide_with_body(
		sanguis::server::entities::with_body const &
	) const;

	virtual
	void
	collision_with_body(
		sanguis::server::entities::with_body & // NOLINT(google-runtime-references)
	); // NOLINT(google-runtime-references)

	[[nodiscard]]
	virtual
	sanguis::collision::world::body_group
	collision_group() const = 0;

	[[nodiscard]]
	virtual
	sanguis::server::speed
	initial_speed() const;

	void
	center_changed(
		sanguis::collision::center
	)
	override;

	void
	speed_changed(
		sanguis::collision::speed const &
	)
	override;

	void
	world_collision()
	override;

	sanguis::server::angle angle_;

	sanguis::server::collision::body collision_body_;

	sanguis::server::net::center net_center_;

	sanguis::server::net::angle net_angle_;
};

}
}
}

#endif
