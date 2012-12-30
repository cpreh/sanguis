#ifndef SANGUIS_SERVER_COLLISION_BODY_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_BODY_HPP_INCLUDED

#include <sanguis/server/collision/body_fwd.hpp>
#include <sanguis/server/collision/position_callback.hpp>
#include <sanguis/server/collision/solidity_fwd.hpp>
#include <sanguis/server/collision/user_data_fwd.hpp>
#include <sanguis/server/angle.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/speed.hpp>
#include <sge/projectile/body/object_fwd.hpp>
#include <sge/projectile/body/position.hpp>
#include <sge/projectile/shape/shared_base_ptr.hpp>
#include <sge/projectile/world_fwd.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr.hpp>

namespace sanguis
{
namespace server
{
namespace collision
{

class body
{
	FCPPT_NONCOPYABLE(
		body
	);
public:
	body(
		server::center const &,
		server::speed const &,
		server::angle,
		sge::projectile::shape::shared_base_ptr,
		collision::solidity const &,
		collision::user_data const &,
		collision::position_callback const &
	);

	~body();

	void
	center(
		server::center const &
	);

	server::center const
	center() const;

	void
	speed(
		server::speed const &
	);

	server::speed const
	speed() const;

	void
	angle(
		server::angle const &
	);

	server::angle const
	angle() const;

	sge::projectile::body::object &
	get();
private:
	void
	on_position_change(
		sge::projectile::body::position const &
	);

	typedef fcppt::scoped_ptr<
		sge::projectile::body::object
	> body_scoped_ptr;

	body_scoped_ptr const body_;

	collision::position_callback const position_callback_;

	fcppt::signal::scoped_connection const position_connection_;
};

}
}
}

#endif

