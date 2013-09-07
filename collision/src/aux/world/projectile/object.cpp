#include <sanguis/collision/duration.hpp>
#include <sanguis/collision/aux/world/projectile/body.hpp>
#include <sanguis/collision/aux/world/projectile/from_sge_user_data.hpp>
#include <sanguis/collision/aux/world/projectile/ghost.hpp>
#include <sanguis/collision/aux/world/projectile/object.hpp>
#include <sanguis/collision/world/body_parameters_fwd.hpp>
#include <sanguis/collision/world/body_unique_ptr.hpp>
#include <sanguis/collision/world/ghost_parameters_fwd.hpp>
#include <sanguis/collision/world/ghost_unique_ptr.hpp>
#include <sanguis/collision/world/object.hpp>
#include <sanguis/collision/world/parameters.hpp>
#include <sge/projectile/duration.hpp>
#include <sge/projectile/time_increment.hpp>
#include <sge/projectile/body/object.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <fcppt/config/external_end.hpp>


sanguis::collision::aux::world::projectile::object::object(
	sanguis::collision::world::parameters const &_parameters
)
:
	sanguis::collision::world::object(),
	impl_(),
	collision_connection_(
		impl_.body_collision(
			[
				_parameters
			](
				sge::projectile::body::object const &_left,
				sge::projectile::body::object const &_right
			)
			{
				_parameters.body_collision_callback()(
					sanguis::collision::aux::world::projectile::from_sge_user_data(
						_left.user_data()
					),
					sanguis::collision::aux::world::projectile::from_sge_user_data(
						_right.user_data()
					)
				);
			}
		)
	),
	global_groups_(
		impl_
	)
{
}

sanguis::collision::aux::world::projectile::object::~object()
{
}

sanguis::collision::world::body_unique_ptr
sanguis::collision::aux::world::projectile::object::create_body(
	sanguis::collision::world::body_parameters const &_parameters
)
{
	return
		fcppt::make_unique_ptr<
			sanguis::collision::aux::world::projectile::body
		>(
			impl_,
			global_groups_,
			_parameters
		);
}

sanguis::collision::world::ghost_unique_ptr
sanguis::collision::aux::world::projectile::object::create_ghost(
	sanguis::collision::world::ghost_parameters const &_parameters
)
{
	return
		fcppt::make_unique_ptr<
			sanguis::collision::aux::world::projectile::ghost
		>(
			impl_,
			global_groups_,
			_parameters
		);
}

void
sanguis::collision::aux::world::projectile::object::update(
	sanguis::collision::duration const _duration
)
{
	impl_.update_continuous(
		sge::projectile::time_increment(
			std::chrono::duration_cast<
				sge::projectile::duration
			>(
				_duration
			)
		)
	);
}
