#include "serialize.hpp"
#include "../base.hpp"
#include <iosfwd>
#include <ostream>

void
sanguis::messages::serialization::serialize(
	ostream &_stream,
	auto_ptr _msg
)
{
	_stream.write(
		reinterpret_cast<
			ostream::char_type const *
		>(
			_msg->data()
		),
		static_cast<
			std::streamsize
		>(
			_msg->size()
		)
	);
}
