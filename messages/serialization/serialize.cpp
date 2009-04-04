#include "serialize.hpp"
#include "../base.hpp"

#include <sge/cerr.hpp>

void
sanguis::messages::serialization::serialize(
	ostream &stream,
	auto_ptr msg)
{
	char test[42];
	stream.write(test, 42);
	/*
	stream.write(
		reinterpret_cast<ostream::char_type const *>(
			msg->data()
		),
		msg->size()
	);*/
}
