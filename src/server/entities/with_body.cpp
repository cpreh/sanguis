#include "with_body.hpp"
#include <fcppt/tr1/functional.hpp>

sanguis::server::entities::with_body::with_body()
:
	collision_body_()	
{
}

sanguis::server::entities::with_body::~with_body()
{
}

sanguis::server::center const
sanguis::server::entities::with_body::center() const
{
	return
		body_->center();
}

void
sanguis::server::entities::with_body::center(
	server::center const &_center
)
{
	body_->center(
		_center
	);
}

void
sanguis::server::entities::with_body::on_transfer(
	collision::create_parameters const &_params
)
{
	collison_body_.take(
		fcppt::make_unique_ptr<
			collision::body
		>(
			_params,
			entities::collision_groups(
				this->type(),
				this->team()
			),
			this->recreate_shape(
				_params.world()
			),
			entities::solidity(
				this->type()
			),
			std::tr1::bind(
				&with_body::on_position_change,
				this,
				std::tr1::placeholders::_1
			)
		)
	);

	with_ghosts::on_transfer(
		_params
	);
}

void
sanguis::server::entities::with_body::on_position_change(
	server::center const &_center
)
{
	with_ghosts::update_center(
		_center
	);
}
