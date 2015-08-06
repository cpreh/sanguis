#ifndef SANGUIS_SERVER_COLLISION_BODY_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_BODY_HPP_INCLUDED

#include <sanguis/collision/world/body_base_fwd.hpp>
#include <sanguis/collision/world/body_enter_container.hpp>
#include <sanguis/collision/world/body_exit_container.hpp>
#include <sanguis/collision/world/body_group_fwd.hpp>
#include <sanguis/collision/world/body_unique_ptr.hpp>
#include <sanguis/collision/world/created_fwd.hpp>
#include <sanguis/collision/world/object_fwd.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/mass.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/speed.hpp>
#include <sanguis/server/collision/body_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_decl.hpp>


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
		sanguis::server::radius,
		sanguis::server::mass,
		sanguis::collision::world::body_base &
	);

	~body();

	void
	center(
		sanguis::server::center
	);

	sanguis::server::center const
	center() const;

	void
	speed(
		sanguis::server::speed
	);

	sanguis::server::speed const
	speed() const;

	sanguis::server::radius const
	radius() const;

	sanguis::collision::world::body_enter_container
	transfer(
		sanguis::collision::world::object &,
		sanguis::collision::world::created,
		sanguis::server::center,
		sanguis::server::speed,
		sanguis::collision::world::body_group
	);

	sanguis::collision::world::body_exit_container
	remove(
		sanguis::collision::world::object &
	);
private:
	sanguis::server::radius const radius_;

	sanguis::server::mass const mass_;

	sanguis::collision::world::body_base &body_base_;

	typedef
	fcppt::optional<
		sanguis::collision::world::body_unique_ptr
	>
	optional_body_unique_ptr;

	optional_body_unique_ptr body_;
};

}
}
}

#endif

