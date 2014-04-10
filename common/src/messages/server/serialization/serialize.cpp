#include <sanguis/messages/server/base_fwd.hpp>
#include <sanguis/messages/server/serialization/serialize.hpp>
#include <alda/serialization/ostream.hpp>
#include <alda/serialization/serialize.hpp>


void
sanguis::messages::server::serialization::serialize(
	alda::serialization::ostream &_stream,
	sanguis::messages::server::base const &_message
)
{
	alda::serialization::serialize(
		_stream,
		_message
	);
}
