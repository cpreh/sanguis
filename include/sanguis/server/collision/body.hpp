#ifndef SANGUIS_SERVER_COLLISION_BODY_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_BODY_HPP_INCLUDED

#include <sanguis/server/angle.hpp>
#include <sanguis/server/center_fwd.hpp>
#include <sanguis/server/speed_fwd.hpp>
#include <sanguis/server/collision/body_fwd.hpp>
#include <sanguis/server/collision/position_callback.hpp>
#include <sanguis/server/collision/solidity_fwd.hpp>
#include <sanguis/server/collision/user_data_fwd.hpp>
#include <sge/projectile/body/object_fwd.hpp>
#include <sge/projectile/body/position.hpp>
#include <sge/projectile/shape/shared_base_ptr.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr_impl.hpp>


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
		sanguis::server::center const &,
		sanguis::server::speed const &,
		sanguis::server::angle,
		sge::projectile::shape::shared_base_ptr,
		sanguis::server::collision::solidity const &,
		sanguis::server::collision::user_data const &,
		sanguis::server::collision::position_callback const &
	);

	~body();

	void
	center(
		sanguis::server::center const &
	);

	sanguis::server::center const
	center() const;

	void
	speed(
		sanguis::server::speed const &
	);

	sanguis::server::speed const
	speed() const;

	void
	angle(
		sanguis::server::angle const &
	);

	sanguis::server::angle const
	angle() const;

	sge::projectile::body::object &
	get();

	sge::projectile::body::object const &
	get() const;
private:
	void
	on_position_change(
		sge::projectile::body::position const &
	);

	typedef fcppt::scoped_ptr<
		sge::projectile::body::object
	> body_scoped_ptr;

	body_scoped_ptr const body_;

	sanguis::server::collision::position_callback const position_callback_;

	fcppt::signal::scoped_connection const position_connection_;
};

}
}
}

#endif

