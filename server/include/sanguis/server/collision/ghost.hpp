#ifndef SANGUIS_SERVER_COLLISION_GHOST_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_GHOST_HPP_INCLUDED

#include <sanguis/collision/world/body_enter_callback.hpp>
#include <sanguis/collision/world/body_exit_callback.hpp>
#include <sanguis/collision/world/ghost_unique_ptr.hpp>
#include <sanguis/collision/world/group_field.hpp>
#include <sanguis/collision/world/object_fwd.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/center_fwd.hpp>
#include <sanguis/server/collision/ghost_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace server
{
namespace collision
{

class ghost
{
	FCPPT_NONCOPYABLE(
		ghost
	);
public:
	ghost(
		sanguis::collision::world::group_field const &,
		sanguis::collision::world::body_enter_callback const &,
		sanguis::collision::world::body_exit_callback const &,
		sanguis::server::radius
	);

	~ghost();

	void
	transfer(
		sanguis::collision::world::object &,
		sanguis::server::center
	);

	void
	destroy();

	void
	center(
		sanguis::server::center
	);
private:
	sanguis::collision::world::group_field const collision_groups_;

	sanguis::collision::world::body_enter_callback const body_enter_callback_;

	sanguis::collision::world::body_exit_callback const body_exit_callback_;

	sanguis::server::radius const radius_;

	sanguis::collision::world::ghost_unique_ptr impl_;
};

}
}
}

#endif
