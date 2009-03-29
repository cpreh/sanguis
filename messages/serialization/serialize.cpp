#include "serialize.hpp"

void
sanguis::messages::serialization::serialize(
	ostream &os,
	auto_ptr msg)
{
	stream.write(
		reinterpret_cast<ostream::value_type *>(
			msg->data()
		),
		msg->size()
	);
}
