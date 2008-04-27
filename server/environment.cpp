#include "environment.hpp"

sanguis::server::environment::environment(const send_callback &send,const insert_callback &insert,const exp_callback &exp)
	: send(send),insert(insert),exp(exp) {}
