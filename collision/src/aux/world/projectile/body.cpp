#include <sanguis/collision/center.hpp>
#include <sanguis/collision/speed.hpp>
#include <sanguis/collision/aux/world/projectile/body.hpp>
#include <sanguis/collision/aux/world/projectile/create_circle.hpp>
#include <sanguis/collision/aux/world/projectile/from_sge_vector.hpp>
#include <sanguis/collision/aux/world/projectile/global_groups_fwd.hpp>
#include <sanguis/collision/aux/world/projectile/make_groups.hpp>
#include <sanguis/collision/aux/world/projectile/to_sge_user_data.hpp>
#include <sanguis/collision/aux/world/projectile/to_sge_vector.hpp>
#include <sanguis/collision/world/body.hpp>
#include <sanguis/collision/world/body_parameters.hpp>
#include <sge/projectile/scalar.hpp>
#include <sge/projectile/world_fwd.hpp>
#include <sge/projectile/body/angular_velocity.hpp>
#include <sge/projectile/body/linear_velocity.hpp>
#include <sge/projectile/body/parameters.hpp>
#include <sge/projectile/body/position.hpp>
#include <sge/projectile/body/rotation.hpp>
#include <sge/projectile/body/scoped.hpp>
#include <sge/projectile/body/solidity/nonsolid.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_unique_ptr.hpp>


sanguis::collision::aux::world::projectile::body::body(
	sanguis::collision::world::body_parameters const &_parameters
)
:
	sanguis::collision::world::body(),
	impl_(
		sge::projectile::body::parameters(
			sge::projectile::body::position(
				sanguis::collision::aux::world::projectile::to_sge_vector(
					_parameters.center().get()
				)
			),
			sge::projectile::body::linear_velocity(
				sanguis::collision::aux::world::projectile::to_sge_vector(
					_parameters.speed().get()
				)
			),
			sge::projectile::body::angular_velocity(
				fcppt::literal<
					sge::projectile::scalar
				>(
					0
				)
			),
			sanguis::collision::aux::world::projectile::create_circle(
				_parameters.radius()
			),
			sge::projectile::body::rotation(
				fcppt::literal<
					sge::projectile::scalar
				>(
					0
				)
			),
			sge::projectile::body::solidity::nonsolid(),
			sanguis::collision::aux::world::projectile::to_sge_user_data(
				_parameters.body_base()
			)
		)
	),
	collision_groups_(
		_parameters.collision_groups()
	),
	position_connection_(
		impl_.position_change(
			[
				_parameters
			](
				sge::projectile::body::position const &_position
			)
			{
				_parameters.position_change_callback()(
					sanguis::collision::center(
						sanguis::collision::aux::world::projectile::from_sge_vector(
							_position.get()
						)
					)
				);
			}
		)
	),
	scoped_()
{
}

sanguis::collision::aux::world::projectile::body::~body()
{
}

void
sanguis::collision::aux::world::projectile::body::activate(
	sge::projectile::world &_world,
	sanguis::collision::aux::world::projectile::global_groups const &_global_groups
)
{
	scoped_.reset();

	scoped_.take(
		fcppt::make_unique_ptr<
			sge::projectile::body::scoped
		>(
			_world,
			impl_,
			sanguis::collision::aux::world::projectile::make_groups(
				collision_groups_,
				_global_groups
			)
		)
	);
}

void
sanguis::collision::aux::world::projectile::body::center(
	sanguis::collision::center const _center
)
{
	impl_.position(
		sanguis::collision::aux::world::projectile::to_sge_vector(
			_center.get()
		)
	);
}

sanguis::collision::center const
sanguis::collision::aux::world::projectile::body::center() const
{
	return
		sanguis::collision::center(
			sanguis::collision::aux::world::projectile::from_sge_vector(
				impl_.position()
			)
		);
}

void
sanguis::collision::aux::world::projectile::body::speed(
	sanguis::collision::speed const _speed
)
{
	impl_.linear_velocity(
		sanguis::collision::aux::world::projectile::to_sge_vector(
			_speed.get()
		)
	);
}

sanguis::collision::speed const
sanguis::collision::aux::world::projectile::body::speed() const
{
	return
		sanguis::collision::speed(
			sanguis::collision::aux::world::projectile::from_sge_vector(
				impl_.linear_velocity()
			)
		);
}
