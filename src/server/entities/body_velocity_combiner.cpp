#include "body_velocity_combiner.hpp"

sanguis::server::entities::body_velocity_combiner::body_velocity_combiner()
{
}

sanguis::server::entities::body_velocity_combiner::~body_velocity_combiner()
{
}

void
sanguis::server::entities::body_velocity_combiner::on_speed_change(
	server::speed const &_speed
)
{
	this->reset_speed(
		_speed
	);
}
