#include <sanguis/messages/client/base.hpp>
#include <sanguis/messages/client/unique_ptr.hpp>
#include <sanguis/messages/client/serialization/deserialize.hpp>
#include <sanguis/messages/client/serialization/global_context.hpp>
#include <alda/serialization/deserialize.hpp>
#include <alda/serialization/istream_fwd.hpp>


sanguis::messages::client::unique_ptr
sanguis::messages::client::serialization::deserialize(
	alda::serialization::istream &_stream
)
{
	return
		alda::serialization::deserialize(
			sanguis::messages::client::serialization::global_context(),
			_stream
		);
}
