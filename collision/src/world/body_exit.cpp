#include <sanguis/collision/world/body_base_fwd.hpp>
#include <sanguis/collision/world/body_exit.hpp>
#include <sanguis/collision/world/ghost_base_fwd.hpp>


sanguis::collision::world::body_exit::body_exit(
	body_ref const _body,
	ghost_ref const _ghost
)
:
	body_(
		_body
	),
	ghost_(
		_ghost
	)
{
}

sanguis::collision::world::body_base &
sanguis::collision::world::body_exit::body() const
{
	return
		body_.get();
}

sanguis::collision::world::ghost_base &
sanguis::collision::world::body_exit::ghost() const
{
	return
		ghost_.get();
}
