#include "serialize.hpp"
#include "../base.hpp"

void
sanguis::messages::serialization::serialize(
	ostream &stream,
	auto_ptr msg)
{
	stream.write(
		reinterpret_cast<ostream::char_type const *>(
			msg->data()
		),
		msg->size()
	);
}
