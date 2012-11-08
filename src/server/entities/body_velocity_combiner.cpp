#include <sanguis/server/speed.hpp>
#include <sanguis/server/entities/body_velocity_combiner.hpp>


sanguis::server::entities::body_velocity_combiner::body_velocity_combiner()
{
}

sanguis::server::entities::body_velocity_combiner::~body_velocity_combiner()
{
}

void
sanguis::server::entities::body_velocity_combiner::on_speed_change(
	sanguis::server::speed const &_speed
)
{
	this->reset_speed(
		_speed
	);
}

sanguis::server::speed const
sanguis::server::entities::body_velocity_combiner::initial_speed() const
{
	return
		this->initial_abs_speed();
}

sanguis::server::speed const
sanguis::server::entities::body_velocity_combiner::actual_speed() const
{
	return
		this->body_speed();
}
