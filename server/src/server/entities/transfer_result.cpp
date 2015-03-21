#include <sanguis/collision/world/body_enter_container.hpp>
#include <sanguis/server/entities/transfer_result.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::transfer_result::transfer_result()
:
	body_enter_()
{
}

sanguis::server::entities::transfer_result::transfer_result(
	sanguis::collision::world::body_enter_container &&_body_enter
)
:
	body_enter_(
		std::move(
			_body_enter
		)
	)
{
}

sanguis::collision::world::body_enter_container const &
sanguis::server::entities::transfer_result::body_enter() const
{
	return
		body_enter_;
}

sanguis::collision::world::body_enter_container &&
sanguis::server::entities::transfer_result::release_body_enter()
{
	return
		std::move(
			body_enter_
		);
}
