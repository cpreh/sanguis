#include <sanguis/collision/world/body_enter_container.hpp>
#include <sanguis/server/collision/transfer_result.hpp>
#include <sanguis/server/entities/transfer_result.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::transfer_result::transfer_result()
:
	collision_result_(
		sanguis::collision::world::body_enter_container()
	)
{
}

sanguis::server::entities::transfer_result::transfer_result(
	sanguis::server::collision::transfer_result &&_collision_result
)
:
	collision_result_(
		std::move(
			_collision_result
		)
	)
{
}

sanguis::server::collision::transfer_result const &
sanguis::server::entities::transfer_result::collision_result() const
{
	return
		collision_result_;
}
