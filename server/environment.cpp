#include "environment.hpp"

sanguis::server::environment::environment(
	send_callback const &send,
	insert_callback const &insert,
	exp_callback const &exp,
	level_callback const &level,
	load_callback const &load,
	sge::collision::system_ptr const collision)
:
	send(send),
	insert(insert),
	exp(exp),
	level(level),
	load(load),
	collision(collision)
{}
