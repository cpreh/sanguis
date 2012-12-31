#include <sanguis/server/center.hpp>
#include <sanguis/server/speed.hpp>
#include <sanguis/server/collision/body.hpp>
#include <sanguis/server/collision/from_sge_vector.hpp>
#include <sanguis/server/collision/solidity.hpp>
#include <sanguis/server/collision/to_sge_vector.hpp>
#include <sanguis/server/collision/to_sge_user_data.hpp>
#include <sge/projectile/body/angular_velocity.hpp>
#include <sge/projectile/body/linear_velocity.hpp>
#include <sge/projectile/body/object.hpp>
#include <sge/projectile/body/parameters.hpp>
#include <sge/projectile/body/position.hpp>
#include <sge/projectile/body/rotation.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sanguis::server::collision::body::body(
	server::center const &_center,
	server::speed const &_speed,
	server::angle const _angle,
	sge::projectile::shape::shared_base_ptr const _shape,
	collision::solidity const &_solidity,
	collision::user_data const &_user_data,
	collision::position_callback const &_position_callback
)
:
	body_(
		fcppt::make_unique_ptr<
			sge::projectile::body::object
		>(
			sge::projectile::body::parameters(
				sge::projectile::body::position(
					collision::to_sge_vector(
						_center.get()
					)
				),
				sge::projectile::body::linear_velocity(
					collision::to_sge_vector(
						_speed.get()
					)
				),
				sge::projectile::body::angular_velocity(
					0.f
				),
				_shape,
				sge::projectile::body::rotation(
					_angle.get() // TODO: convert?
				),
				_solidity.get(),
				collision::to_sge_user_data(
					_user_data
				)
			)
		)
	),
	position_callback_(
		_position_callback
	),
	position_connection_(
		body_->position_change(
			std::bind(
				&collision::body::on_position_change,
				this,
				std::placeholders::_1
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
	sanguis::server::speed const &_speed
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
sanguis::server::collision::body::angle(
	server::angle const &_angle
)
{
	body_->rotation(
		_angle.get()
	);
}

sanguis::server::angle const
sanguis::server::collision::body::angle() const
{
	return
		server::angle(
			body_->rotation()
		);
}

sge::projectile::body::object &
sanguis::server::collision::body::get()
{
	return *body_;
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
