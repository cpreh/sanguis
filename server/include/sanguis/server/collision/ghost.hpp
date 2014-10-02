#ifndef SANGUIS_SERVER_COLLISION_GHOST_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_GHOST_HPP_INCLUDED

#include <sanguis/collision/world/body_enter_callback.hpp>
#include <sanguis/collision/world/body_exit_callback.hpp>
#include <sanguis/collision/world/ghost_group.hpp>
#include <sanguis/collision/world/ghost_unique_ptr.hpp>
#include <sanguis/collision/world/object_fwd.hpp>
#include <sanguis/server/center_fwd.hpp>
#include <sanguis/server/radius.hpp>
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
		sanguis::collision::world::ghost_group,
		sanguis::collision::world::body_enter_callback const &,
		sanguis::collision::world::body_exit_callback const &,
		sanguis::server::radius
	);

	ghost(
		ghost &&
	);

	ghost &
	operator=(
		ghost &&
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
	sanguis::collision::world::ghost_group collision_group_;

	sanguis::collision::world::body_enter_callback body_enter_callback_;

	sanguis::collision::world::body_exit_callback body_exit_callback_;

	sanguis::server::radius radius_;

	sanguis::collision::world::ghost_unique_ptr impl_;
};

}
}
}

#endif
