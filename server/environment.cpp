#include "environment.hpp"

sanguis::server::environment::environment(
	send_callback const &send,
	insert_callback const &insert,
	exp_callback const &exp,
	level_callback const &level,
	load_callback const &load,
	spawn_pickup_callback const &spawn_pickup,
	pickup_chance_callback const &pickup_chance,
	sge::collision::world_ptr const collision_)
:
	send(send),
	insert(insert),
	exp(exp),
	level(level),
	load(load),
	spawn_pickup(spawn_pickup),
	pickup_chance(pickup_chance),
	collision_(collision_)
{}

sge::collision::world_ptr const
sanguis::server::environment::collision() const
{
	return collision_;
}
