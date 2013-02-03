#include <sanguis/server/collision/body_collision.hpp>
#include <sanguis/server/collision/body_base.hpp>
#include <sanguis/server/collision/from_sge_user_data.hpp>
#include <sanguis/server/collision/user_data.hpp>
#include <sge/projectile/body/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/logic/tribool.hpp>
#include <fcppt/config/external_end.hpp>


namespace
{

void
execute_collision(
	sanguis::server::collision::body_base &,
	sanguis::server::collision::body_base &
);

}

void
sanguis::server::collision::body_collision(
	sge::projectile::body::object const &_a,
	sge::projectile::body::object const &_b
)
{
	if(
		_a.user_data().empty()
		||
		_b.user_data().empty()
	)
		return;

	sanguis::server::collision::body_base
		&base_a(
			sanguis::server::collision::from_sge_user_data(
				_a.user_data()
			).get()
		),
		&base_b(
			sanguis::server::collision::from_sge_user_data(
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
		_a.collision(
			_b
		);
}

}
