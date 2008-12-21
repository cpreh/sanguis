#include "environment.hpp"

sanguis::server::environment::environment(
	send_callback const &send,
	insert_callback const &insert,
	exp_callback const &exp,
	level_callback const &level,
	load_callback const &load)
:
	send(send),
	insert(insert),
	exp(exp),
	level(level),
	load(load)
{}
