#ifndef SANGUIS_SERVER_ENTITIES_WITH_BODY_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_BODY_HPP_INCLUDED

#include <sanguis/collision/world/body_base.hpp>
#include <sanguis/collision/world/body_group_fwd.hpp>
#include <sanguis/server/angle.hpp>
#include <sanguis/server/center_fwd.hpp>
#include <sanguis/server/dim.hpp>
#include <sanguis/server/model_size_fwd.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/speed_fwd.hpp>
#include <sanguis/server/collision/body.hpp>
#include <sanguis/server/collision/body_fwd.hpp>
#include <sanguis/server/collision/result_fwd.hpp>
#include <sanguis/server/entities/optional_transfer_result_fwd.hpp>
#include <sanguis/server/entities/remove_from_world_result_fwd.hpp>
#include <sanguis/server/entities/transfer_parameters_fwd.hpp>
#include <sanguis/server/entities/with_body_fwd.hpp>
#include <sanguis/server/entities/with_ghosts.hpp>
#include <sanguis/server/entities/ifaces/with_angle.hpp>
#include <sanguis/server/entities/ifaces/with_id.hpp>
#include <sanguis/server/entities/ifaces/with_links.hpp>
#include <sanguis/server/net/angle.hpp>
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
		sanguis::server::model_size
	);

	~with_body()
	override;

	// entities::base overridden functions
	sanguis::server::center const
	center() const
	override;

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

	sanguis::server::dim const
	dim() const;

	sanguis::server::entities::remove_from_world_result
	remove_from_world()
	override;
protected:
	// entities::base::on_transfer
	sanguis::server::entities::optional_transfer_result
	on_transfer(
		sanguis::server::entities::transfer_parameters const &
	)
	override;

	virtual
	void
	on_world_collision(
		sanguis::server::collision::result const &
	);

	void
	update()
	override;

	void
	body_speed(
		sanguis::server::speed
	);

	sanguis::server::speed const
	body_speed() const;
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
	sanguis::collision::world::body_group
	collision_group() const = 0;

	virtual
	sanguis::server::speed const
	initial_speed() const;

	void
	position_change(
		sanguis::server::center
	);

	virtual
	void
	on_position_change(
		sanguis::server::center
	);

	virtual
	void
	on_speed_change(
		sanguis::server::speed
	);

	sanguis::server::dim const dim_;

	sanguis::server::angle angle_;

	sanguis::server::collision::body collision_body_;

	sanguis::server::net::angle net_angle_;
};

}
}
}

#endif
