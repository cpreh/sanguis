#include "with_body.hpp"

sanguis::server::entities::with_body::with_body()
:
	collision_body_()	
{
}

sanguis::server::entities::with_body::~with_body()
{
}

void
sanguis::server::entities::with_body::on_update(
	sanguis::time_type const _time
)
{
}

void
sanguis::server::entities::with_body::on_transfer(
	collision::global_groups const &_collision_groups,
	collision::create_parameters const &_params
)
{
	collison_body_.take(
		fcppt::make_unique_ptr<
			collision::body
		>(
			this->environment()->collision_world(),
			_params,
			this->recreate_shape(
				collision::shape_parameters(
					this->environment()->collision_world()
				)
			),
			this->recreate_ghosts(
				collision::ghost_parameters(
					_collision_groups,
					this->environment()->collision_world()
				)
			)
		)
	);
}

void
sanguis::server::entities::with_body::on_center(
	server::pos const &_center
)
{
}
