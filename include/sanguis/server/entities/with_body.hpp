#ifndef SANGUIS_SERVER_ENTITIES_WITH_BODY_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_BODY_HPP_INCLUDED

#include <sanguis/server/entities/with_body_fwd.hpp>
#include <sanguis/server/entities/body_parameters_fwd.hpp>
#include <sanguis/server/entities/transfer_parameters_fwd.hpp>
#include <sanguis/server/entities/with_ghosts.hpp>
#include <sanguis/server/entities/ifaces/with_angle.hpp>
#include <sanguis/server/entities/ifaces/with_body.hpp>
#include <sanguis/server/collision/body_base.hpp>
#include <sanguis/server/collision/body_fwd.hpp>
#include <sanguis/server/angle.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/speed.hpp>
#include <sge/projectile/body/scoped_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr.hpp>
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
	public virtual entities::with_ghosts,
	protected virtual ifaces::with_body,
	public virtual ifaces::with_angle,
	public collision::body_base
{
	FCPPT_NONCOPYABLE(
		with_body
	);
public:
	explicit with_body(
		entities::body_parameters const &
	);

	~with_body();

	// entities::base overridden functions
	server::center const
	center() const;

	// ifaces::with_angle overridden functions
	server::angle const
	angle() const;

	// own functions
	void
	center(
		server::center const &
	);

	void
	speed(
		server::speed const &
	);

	void
	angle(
		server::angle
	);
protected:
	// entities::base::on_transfer
	void
	on_transfer(
		entities::transfer_parameters const &
	);

	void
	on_destroy();
private:
	void
	on_position_change(
		server::center const &
	);

	// collision::body_base
	boost::logic::tribool const
	can_collide_with(
		collision::body_base const &
	) const;

	void
	collision(
		collision::body_base &
	);

	virtual boost::logic::tribool const
	can_collide_with_body(
		entities::with_body const &
	) const;

	virtual void
	collision_with_body(
		entities::with_body &
	);

	// ifaces::with_body
	void
	reset_speed(
		server::speed const &
	);

	typedef fcppt::scoped_ptr<
		collision::body
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
