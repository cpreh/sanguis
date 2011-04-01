#include "body.hpp"
#include "create_parameters.hpp"
#include "from_sge_pos.hpp"
#include "ghost_parameters.hpp"
#include "global_groups.hpp"
#include "to_sge_vector.hpp"
#include "to_sge_user_data.hpp"
#include <sge/projectile/body/object.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <boost/foreach.hpp>

sanguis::server::collision::body::body(
	sge::projectile::world &_world,
	collision::create_parameters const &_create_param,
	collision::global_groups const &_global_groups,
	collision::group_vector const &_collision_groups,
	collision::shape_unique_ptr _shape,
	collision::solidity const &_solidity,
	collision::ghost_reference_vector const &_ghost_references
)
:
	body_(
		fcppt::make_unique_ptr<
			sge::projectile::body::object
		>(
			sge::projectile::body::parameters(
				_world,
				sge::projectile::body::position(
					collision::to_sge_vector(
						_create_param.center().get()
					)
				),
				sge::projectile::body::linear_velocity(
					collision::to_sge_vector(
						_create_param.speed().get()
					)
				),
				sge::projectile::body::angular_velocity(
					0.f
				),
				_shape,
				sge::projectile::body::rotation(
					0.f
				),
				_solidty.get(),
				collision::make_groups(
					_collision_groups,
					_global_groups
				),
				collision::to_sge_user_data(
					_create_param.user_data()
				)
			)
		)
	),
	position_change_connection_(
		body_->position_change(
			std::tr1::bind(
				&collision::body::on_pos_change,
				this,
				std::tr1::placeholders::_1
			)
		)
	),
	ghosts_references_(_ghost_references)
{
}

sanguis::server::collision::body::~body()
{
}

void
sanguis::server::collision::body::body_pos(
	server::pos const &_pos
)
{
	body_->position(
		collision::to_sge_pos(
			_pos
		)
	);

	// TODO: on_position_change here?
}

sanguis::server::pos const
sanguis::server::collision::body::body_pos() const
{
	return
		collision::from_sge_pos(
			body_->position()
		);
}

void
sanguis::server::collision::body::body_speed(
	server::pos const &_speed
)
{
	body_->linear_velocity(
		sge::projectile::body::linear_velocity(
			collision::to_sge_pos(
				_speed
			)
		)
	);
}

sanguis::server::pos_type const
sanguis::server::collision::body::body_speed() const
{
	return
		fcppt::math::vector::narrow_cast<
			server::pos
		>(
			body_->linear_velocity()
		);
}

void
sanguis::server::collision::body::on_position_change(
	sge::projectile::body::position const &_position
)
{
	BOOST_FOREACH(
		collision::ghost_reference_vector::value_type ghost,
		ghosts_references_
	)
		ghost.get().position(
			_postion
		);
}
