#include <sanguis/collision/world/body_exit_container.hpp>
#include <sanguis/server/collision/remove_result.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::collision::remove_result::remove_result(
	sanguis::collision::world::body_exit_container &&_body_exit
)
:
	body_exit_(
		std::move(
			_body_exit
		)
	)
{
}

sanguis::collision::world::body_exit_container const &
sanguis::server::collision::remove_result::body_exit() const
{
	return
		body_exit_;
}

sanguis::collision::world::body_exit_container &&
sanguis::server::collision::remove_result::release_body_exit()
{
	return
		std::move(
			body_exit_
		);
}
