#include <sanguis/collision/duration.hpp>
#include <sanguis/collision/aux_/world/projectile/body.hpp>
#include <sanguis/collision/aux_/world/projectile/from_sge_user_data.hpp>
#include <sanguis/collision/aux_/world/projectile/ghost.hpp>
#include <sanguis/collision/aux_/world/projectile/object.hpp>
#include <sanguis/collision/world/body.hpp>
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
#include <fcppt/cast/static_downcast.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <fcppt/config/external_end.hpp>


sanguis::collision::aux_::world::projectile::object::object(
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
					sanguis::collision::aux_::world::projectile::from_sge_user_data(
						_left.user_data()
					),
					sanguis::collision::aux_::world::projectile::from_sge_user_data(
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

sanguis::collision::aux_::world::projectile::object::~object()
{
}

sanguis::collision::world::body_unique_ptr
sanguis::collision::aux_::world::projectile::object::create_body(
	sanguis::collision::world::body_parameters const &_parameters
)
{
	return
		fcppt::make_unique_ptr<
			sanguis::collision::aux_::world::projectile::body
		>(
			_parameters
		);
}

void
sanguis::collision::aux_::world::projectile::object::activate_body(
	sanguis::collision::world::body &_body
)
{
	fcppt::cast::static_downcast<
		sanguis::collision::aux_::world::projectile::body &
	>(
		_body
	).activate(
		impl_,
		global_groups_
	);
}

sanguis::collision::world::ghost_unique_ptr
sanguis::collision::aux_::world::projectile::object::create_ghost(
	sanguis::collision::world::ghost_parameters const &_parameters
)
{
	return
		fcppt::make_unique_ptr<
			sanguis::collision::aux_::world::projectile::ghost
		>(
			impl_,
			global_groups_,
			_parameters
		);
}

void
sanguis::collision::aux_::world::projectile::object::update(
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
