#include <sanguis/collision/impl/world/simple/ghost_result.hpp>
#include <sanguis/collision/world/body_enter_container.hpp>
#include <sanguis/collision/world/body_exit_container.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::collision::impl::world::simple::ghost_result::ghost_result(
	sanguis::collision::world::body_enter_container &&_body_enter,
	sanguis::collision::world::body_exit_container &&_body_exit
)
:
	body_enter_(
		std::move(
			_body_enter
		)
	),
	body_exit_(
		std::move(
			_body_exit
		)
	)
{
}

sanguis::collision::world::body_enter_container &&
sanguis::collision::impl::world::simple::ghost_result::release_body_enter()
{
	return
		std::move(
			body_enter_
		);
}

sanguis::collision::world::body_exit_container &&
sanguis::collision::impl::world::simple::ghost_result::release_body_exit()
{
	return
		std::move(
			body_exit_
		);
}
