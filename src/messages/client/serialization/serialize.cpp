#include <sanguis/messages/client/base_fwd.hpp>
#include <sanguis/messages/client/serialization/serialize.hpp>
#include <alda/serialization/ostream.hpp>
#include <alda/serialization/serialize.hpp>


void
sanguis::messages::client::serialization::serialize(
	alda::serialization::ostream &_stream,
	sanguis::messages::client::base const &_message
)
{
	alda::serialization::serialize(
		_stream,
		_message
	);
}
