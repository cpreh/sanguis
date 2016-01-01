#ifndef SANGUIS_SERVER_COLLISION_GHOST_HPP_INCLUDED
#define SANGUIS_SERVER_COLLISION_GHOST_HPP_INCLUDED

#include <sanguis/collision/world/body_enter_container.hpp>
#include <sanguis/collision/world/body_exit_container.hpp>
#include <sanguis/collision/world/ghost_base_fwd.hpp>
#include <sanguis/collision/world/ghost_group.hpp>
#include <sanguis/collision/world/ghost_unique_ptr.hpp>
#include <sanguis/collision/world/object_fwd.hpp>
#include <sanguis/server/center_fwd.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/collision/ghost_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/reference_wrapper_decl.hpp>
#include <fcppt/optional/object_decl.hpp>


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
		sanguis::collision::world::ghost_base &,
		sanguis::collision::world::ghost_group,
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

	sanguis::collision::world::body_enter_container
	transfer(
		sanguis::collision::world::object &,
		sanguis::server::center
	);

	sanguis::collision::world::body_exit_container
	destroy(
		sanguis::collision::world::object &
	);

	void
	center(
		sanguis::server::center
	);
private:
	typedef
	fcppt::reference_wrapper<
		sanguis::collision::world::ghost_base
	>
	ghost_base_ref;

	ghost_base_ref ghost_base_;

	sanguis::collision::world::ghost_group collision_group_;

	sanguis::server::radius radius_;

	typedef
	fcppt::optional::object<
		sanguis::collision::world::ghost_unique_ptr
	>
	optional_ghost_unique_ptr;

	optional_ghost_unique_ptr impl_;
};

}
}
}

#endif
