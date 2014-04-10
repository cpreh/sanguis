#include <sanguis/collision/world/body_base.hpp>
#include <sanguis/server/collision/body_collision.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/logic/tribool.hpp>
#include <fcppt/config/external_end.hpp>


namespace
{

void
execute_collision(
	sanguis::collision::world::body_base &,
	sanguis::collision::world::body_base &
);

}

void
sanguis::server::collision::body_collision(
	sanguis::collision::world::body_base &_body_a,
	sanguis::collision::world::body_base &_body_b
)
{
	execute_collision(
		_body_a,
		_body_b
	);

	execute_collision(
		_body_b,
		_body_a
	);
}

namespace
{

void
execute_collision(
	sanguis::collision::world::body_base &_a,
	sanguis::collision::world::body_base &_b
)
{
	if(
		_a.can_collide_with(
			_b
		)
	)
		_a.collision(
			_b
		);
}

}
