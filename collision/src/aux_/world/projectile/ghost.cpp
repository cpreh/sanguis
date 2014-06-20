#include <sanguis/collision/center.hpp>
#include <sanguis/collision/dim2.hpp>
#include <sanguis/collision/unit.hpp>
#include <sanguis/collision/aux_/world/projectile/from_sge_user_data.hpp>
#include <sanguis/collision/aux_/world/projectile/global_groups_fwd.hpp>
#include <sanguis/collision/aux_/world/projectile/ghost.hpp>
#include <sanguis/collision/aux_/world/projectile/make_groups.hpp>
#include <sanguis/collision/aux_/world/projectile/to_sge_dim.hpp>
#include <sanguis/collision/aux_/world/projectile/to_sge_vector.hpp>
#include <sanguis/collision/world/body_callback.hpp>
#include <sanguis/collision/world/ghost.hpp>
#include <sanguis/collision/world/ghost_parameters.hpp>
#include <sge/projectile/world_fwd.hpp>
#include <sge/projectile/body/object.hpp>
#include <sge/projectile/ghost/parameters.hpp>
#include <sge/projectile/ghost/position.hpp>
#include <sge/projectile/ghost/object.hpp>
#include <sge/projectile/ghost/size.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/dim/fill.hpp>
#include <fcppt/signal/auto_connection.hpp>


sanguis::collision::aux_::world::projectile::ghost::ghost(
	sge::projectile::world &_world,
	sanguis::collision::aux_::world::projectile::global_groups const &_global_groups,
	sanguis::collision::world::ghost_parameters const &_parameters
)
:
	sanguis::collision::world::ghost(),
	impl_(
		sge::projectile::ghost::parameters(
			sge::projectile::ghost::position(
				sanguis::collision::aux_::world::projectile::to_sge_vector(
					_parameters.center().get()
				)
			),
			sge::projectile::ghost::size(
				sanguis::collision::aux_::world::projectile::to_sge_dim(
					fcppt::math::dim::fill<
						sanguis::collision::dim2::dim_wrapper::value
					>(
						_parameters.radius().get()
					)
					*
					fcppt::literal<
						sanguis::collision::unit
					>(
						2
					)
				)
			)
		)
	),
	collision_begin_connection_(
		this->make_connection(
			&sge::projectile::ghost::object::body_enter,
			_parameters.body_enter_callback().get()
		)
	),
	collision_end_connection_(
		this->make_connection(
			&sge::projectile::ghost::object::body_exit,
			_parameters.body_exit_callback().get()
		)
	),
	scoped_(
		_world,
		impl_,
		sanguis::collision::aux_::world::projectile::make_groups(
			_parameters.collision_group(),
			_global_groups
		)
	)
{
}

sanguis::collision::aux_::world::projectile::ghost::~ghost()
{
}

void
sanguis::collision::aux_::world::projectile::ghost::center(
	sanguis::collision::center const _center
)
{
	impl_.position(
		sanguis::collision::aux_::world::projectile::to_sge_vector(
			_center.get()
		)
	);
}

template<
	typename SgeFunction
>
fcppt::signal::auto_connection
sanguis::collision::aux_::world::projectile::ghost::make_connection(
	SgeFunction const _function,
	sanguis::collision::world::body_callback const &_callback
)
{
	return
		(
			impl_.*_function
		)(
			[
				_callback
			](
				sge::projectile::body::object const &_body
			)
			{
				_callback(
					sanguis::collision::aux_::world::projectile::from_sge_user_data(
						_body.user_data()
					)
				);
			}
		);
}
