#include "environment.hpp"

sanguis::server::environment::environment(
	send_callback const &send_,
	insert_callback const &insert_,
	exp_callback const &exp_,
	level_callback const &level_,
	load_callback const &load_,
	spawn_pickup_callback const &spawn_pickup_,
	pickup_chance_callback const &pickup_chance_,
	sge::collision::world_ptr const collision_)
:
	send_(send_),
	insert_(insert_),
	exp_(exp_),
	level_(level_),
	load_(load_),
	spawn_pickup_(spawn_pickup_),
	pickup_chance_(pickup_chance_),
	collision_(collision_)
{}

sanguis::server::send_callback const &
sanguis::server::environment::send() const
{
	return send_;
}

sanguis::server::insert_callback const &
sanguis::server::environment::insert() const
{
	return insert_;
}

sanguis::server::exp_callback const &
sanguis::server::environment::exp() const
{
	return exp_;
}

sanguis::server::level_callback const &
sanguis::server::environment::level() const
{
	return level_;
}

sanguis::server::load_callback const &
sanguis::server::environment::load() const
{
	return load_;
}

sanguis::server::spawn_pickup_callback const &
sanguis::server::environment::spawn_pickup() const
{
	return spawn_pickup_;
}

sanguis::server::pickup_chance_callback const &
sanguis::server::environment::pickup_chance() const
{
	return pickup_chance_;
}

sge::collision::world_ptr const
sanguis::server::environment::collision() const
{
	return collision_;
}
