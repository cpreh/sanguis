#include "body_collision.hpp"
#include "body_base.hpp"
#include "from_sge_user_data.hpp"
#include "user_data.hpp"
#include <sge/projectile/body/object.hpp>
#include <boost/logic/tribool.hpp>

namespace
{

void
execute_collision(
	sanguis::server::collision::base &,
	sanguis::server::collision::base &
);

}

void
sanguis::server::collision::body_collision(
	sge::projectile::body::object const &_a,
	sge::projectile::body::object const &_b
)
{
	collision::body_base
		&base_a(
			collision::from_sge_user_data(
				_a.user_data()
			).get()
		),
		&base_b(
			collision::from_sge_user_data(
				_b.user_data()
			).get()
		);
	
	execute_collision(
		base_a,
		base_b
	);

	execute_collision(
		base_b,
		base_a
	);
}

namespace
{

void
execute_collision(
	sanguis::server::collision::body_base &_a,
	sanguis::server::collision::body_base &_b
)
{
	if(
		_a.can_collide_with(
			_b
		)
	)
		_a.collide(
			_b
		);
}

}
