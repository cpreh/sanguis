#include "environment.hpp"

sanguis::server::environment::environment(
	send_callback const &send,
	insert_callback const &insert,
	exp_callback const &exp,
	level_callback const &level,
	load_callback const &load,
	sge::collision::world_ptr const collision_)
:
	send(send),
	insert(insert),
	exp(exp),
	level(level),
	load(load),
	collision_(collision_)
{}

sge::collision::world_ptr const
sanguis::server::environment::collision() const
{
	return collision_;
}
