#include <sanguis/collision/world/body_enter_container.hpp>
#include <sanguis/server/collision/transfer_result.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::collision::transfer_result::transfer_result(
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
sanguis::server::collision::transfer_result::body_enter() const
{
	return
		body_enter_;
}
