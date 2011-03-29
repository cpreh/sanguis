#include "body.hpp"
#include "create_parameters.hpp"
#include "from_sge_pos.hpp"
#include "global_groups.hpp"
#include "to_sge_pos.hpp"
#include <sge/projectile/body/object.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/make_unique_ptr.hpp>

sanguis::server::collision::body::body()
:
	body_(),
	shapes_()
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
sanguis::server::collision::body::recreate(
	sge::projectile::world &_world,
	collision::global_groups const &_global_groups,
	collision::create_parameters const &_create_param
)
{
	body_.take(
		fcppt::make_unique_ptr<
			sge::projectile::body::object
		>(
			sge::projectile::body::parameters(
				_world,
				sge::projectile::body::position(
					collision::to_sge_pos(
						_create_param.center()
					)
				),
				sge::projectile::body::linear_velocity(
					collision::to_sge_pos(
						_create_param.speed()
					)
				),
				sge::projectile::body::angular_velocity(
					0.f
				),
				this->recreate_shape(
					_world
				),
				sge::projectile::body::rotation(
					0.f
				),
				this->solidty(),
					
			)
		)
	);
}

void
sanguis::server::collision::body::destroy()
{
	this->on_destroy();

	body_.reset();
}

sanguis::server::collision::body::~body()
{}

void
sanguis::server::collision::body::on_destroy()
{}
