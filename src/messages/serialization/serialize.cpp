#include <sanguis/messages/base_fwd.hpp>
#include <sanguis/messages/serialization/serialize.hpp>
#include <alda/serialization/ostream.hpp>
#include <alda/serialization/serialize.hpp>
#include <fcppt/config/external_begin.hpp>
#include <iosfwd>
#include <ostream>
#include <fcppt/config/external_end.hpp>

void
sanguis::messages::serialization::serialize(
	alda::serialization::ostream &_stream,
	sanguis::messages::base const &_message
)
{
	alda::serialization::serialize(
		_stream,
		_message
	);
}
