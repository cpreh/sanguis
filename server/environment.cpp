#include "environment.hpp"

sanguis::server::environment::environment(const send_callback &send,const insert_callback &insert)
	: send(send),insert(insert) {}
