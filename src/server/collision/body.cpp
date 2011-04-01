#include "body.hpp"
#include "create_parameters.hpp"
#include "from_sge_vector.hpp"
#include "ghost_parameters.hpp"
#include "global_groups.hpp"
#include "make_groups.hpp"
#include "solidity.hpp"
#include "to_sge_vector.hpp"
#include "to_sge_user_data.hpp"
#include "../center.hpp"
#include "../speed.hpp"
#include <sge/projectile/body/angular_velocity.hpp>
#include <sge/projectile/body/linear_velocity.hpp>
#include <sge/projectile/body/object.hpp>
#include <sge/projectile/body/parameters.hpp>
#include <sge/projectile/body/position.hpp>
#include <sge/projectile/body/rotation.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <boost/foreach.hpp>

sanguis::server::collision::body::body(
	sge::projectile::world &_world,
	collision::create_parameters const &_create_param,
	collision::group_vector const &_collision_groups,
	sge::projectile::shape::shared_base_ptr const _shape,
	collision::solidity const &_solidity,
	collision::position_callback const &_position_callback
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
				_solidity.get(),
				collision::make_groups(
					_collision_groups,
					_create_param.global_groups()
				),
				collision::to_sge_user_data(
					_create_param.user_data()
				)
			)
		)
	),
	position_callback_(
		_position_callback
	),
	position_connection_(
		body_->position_change(
			std::tr1::bind(
				&collision::body::on_position_change,
				this,
				std::tr1::placeholders::_1
			)
		)
	)
{
}

sanguis::server::collision::body::~body()
{
}

void
sanguis::server::collision::body::center(
	server::center const &_center
)
{
	body_->position(
		collision::to_sge_vector(
			_center.get()
		)
	);
}

sanguis::server::center const
sanguis::server::collision::body::center() const
{
	return
		server::center(
			collision::from_sge_vector(
				body_->position()
			)
		);
}

void
sanguis::server::collision::body::speed(
	server::speed const &_speed
)
{
	body_->linear_velocity(
		collision::to_sge_vector(
			_speed.get()
		)
	);
}

sanguis::server::speed const
sanguis::server::collision::body::speed() const
{
	return
		server::speed(
			collision::from_sge_vector(
				body_->linear_velocity()
			)
		);
}

void
sanguis::server::collision::body::on_position_change(
	sge::projectile::body::position const &_position
)
{
	position_callback_(
		server::center(
			collision::from_sge_vector(
				_position.get()
			)
		)
	);
}
