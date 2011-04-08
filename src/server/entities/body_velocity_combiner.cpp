#include "body_velocity_combiner.hpp"
#include <fcppt/math/vector/basic_impl.hpp>

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

sanguis::server::speed const
sanguis::server::entities::body_velocity_combiner::initial_speed() const
{
	return
		this->initial_abs_speed();
}
