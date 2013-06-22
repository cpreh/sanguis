#ifndef SANGUIS_SERVER_ENTITIES_WITH_BODY_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_BODY_HPP_INCLUDED

#include <sanguis/server/angle.hpp>
#include <sanguis/server/center_fwd.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/speed_fwd.hpp>
#include <sanguis/server/collision/result_fwd.hpp>
#include <sanguis/server/entities/body_parameters_fwd.hpp>
#include <sanguis/server/entities/transfer_parameters_fwd.hpp>
#include <sanguis/server/entities/with_body_fwd.hpp>
#include <sanguis/server/entities/with_ghosts.hpp>
#include <sanguis/server/entities/ifaces/with_angle.hpp>
#include <sanguis/server/entities/ifaces/with_body.hpp>
#include <sanguis/server/collision/body_base.hpp>
#include <sanguis/server/collision/body_fwd.hpp>
#include <sge/projectile/body/scoped_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr_impl.hpp>
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
	public sanguis::server::collision::body_base
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
	center() const;

	virtual
	void
	world_collision(
		sanguis::server::collision::result const &
	);

	// ifaces::with_angle overridden functions
	sanguis::server::angle const
	angle() const;

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
	);

	void
	on_destroy();
private:
	void
	on_position_change(
		sanguis::server::center const &
	);

	// collision::body_base
	boost::logic::tribool const
	can_collide_with(
		sanguis::server::collision::body_base const &
	) const;

	void
	collision(
		sanguis::server::collision::body_base &
	);

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

	// ifaces::with_body
	void
	reset_speed(
		sanguis::server::speed const &
	);

	sanguis::server::speed const
	body_speed() const;

	sanguis::server::radius const radius_;

	typedef fcppt::scoped_ptr<
		sanguis::server::collision::body
	> body_scoped_ptr;

	body_scoped_ptr collision_body_;

	typedef fcppt::scoped_ptr<
		sge::projectile::body::scoped
	> scoped_body_scope_ptr;

	scoped_body_scope_ptr scoped_body_;
};

}
}
}

#endif
