#include <sanguis/collision/world/body_base.hpp>
#include <sanguis/collision/world/body_collision.hpp>
#include <sanguis/collision/world/body_collision_container.hpp>
#include <sanguis/server/collision/body_collision.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/logic/tribool.hpp>
#include <fcppt/config/external_end.hpp>


void
sanguis::server::collision::body_collision(
	sanguis::collision::world::body_collision_container const &_collisions
)
{
	auto const execute_collision(
		[](
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
	);

	for(
		sanguis::collision::world::body_collision const &cur
		:
		_collisions
	)
	{
		execute_collision(
			cur.body1(),
			cur.body2()
		);

		execute_collision(
			cur.body2(),
			cur.body1()
		);
	}
}
