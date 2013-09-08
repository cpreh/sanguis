#ifndef SANGUIS_SERVER_ENTITIES_WITH_BODY_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_BODY_HPP_INCLUDED

#include <sanguis/collision/world/body_base.hpp>
#include <sanguis/collision/world/group_field_fwd.hpp>
#include <sanguis/server/angle.hpp>
#include <sanguis/server/center_fwd.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/speed_fwd.hpp>
#include <sanguis/server/collision/body.hpp>
#include <sanguis/server/collision/result_fwd.hpp>
#include <sanguis/server/entities/body_parameters_fwd.hpp>
#include <sanguis/server/entities/transfer_parameters_fwd.hpp>
#include <sanguis/server/entities/with_body_fwd.hpp>
#include <sanguis/server/entities/with_ghosts.hpp>
#include <sanguis/server/entities/ifaces/with_angle.hpp>
#include <sanguis/server/entities/ifaces/with_body.hpp>
#include <sanguis/server/entities/ifaces/with_id.hpp>
#include <sanguis/server/entities/ifaces/with_links.hpp>
#include <sanguis/server/collision/body_fwd.hpp>
#include <sge/projectile/body/scoped_fwd.hpp>
#include <fcppt/noncopyable.hpp>
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
	protected virtual sanguis::server::entities::ifaces::with_body,
	public virtual sanguis::server::entities::ifaces::with_angle,
	public virtual sanguis::server::entities::ifaces::with_id,
	public virtual sanguis::server::entities::ifaces::with_links,
	public sanguis::collision::world::body_base
{
	FCPPT_NONCOPYABLE(
		with_body
	);
public:
	explicit
	with_body(
		sanguis::server::entities::body_parameters const &
	);

	~with_body();

	// entities::base overridden functions
	sanguis::server::center const
	center() const
	override;

	virtual
	void
	world_collision(
		sanguis::server::collision::result const &
	);

	// ifaces::with_angle overridden functions
	sanguis::server::angle const
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
	);

	sanguis::server::radius const
	radius() const;
protected:
	// entities::base::on_transfer
	bool
	on_transfer(
		sanguis::server::entities::transfer_parameters const &
	)
	override;

	void
	on_destroy()
	override;
private:
	// collision::body_base
	boost::logic::tribool const
	can_collide_with(
		sanguis::collision::world::body_base const &
	) const
	override;

	void
	collision(
		sanguis::collision::world::body_base &
	)
	override;

	virtual
	boost::logic::tribool const
	can_collide_with_body(
		sanguis::server::entities::with_body const &
	) const;

	virtual
	void
	collision_with_body(
		sanguis::server::entities::with_body &
	);

	virtual
	sanguis::collision::world::group_field const
	collision_groups() const = 0;

	// ifaces::with_body
	void
	reset_speed(
		sanguis::server::speed const &
	)
	override;

	sanguis::server::speed const
	body_speed() const
	override;

	void
	on_position_change(
		sanguis::server::center
	);

	sanguis::server::angle angle_;

	sanguis::server::collision::body collision_body_;
};

}
}
}

#endif
