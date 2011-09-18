#include <sanguis/messages/serialization/serialize.hpp>
#include <sanguis/messages/base.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <ostream>
#include <fcppt/config/external_end.hpp>

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
