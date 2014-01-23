#include <sanguis/messages/server/base.hpp>
#include <sanguis/messages/server/unique_ptr.hpp>
#include <sanguis/messages/server/serialization/deserialize.hpp>
#include <sanguis/messages/server/serialization/global_context.hpp>
#include <alda/serialization/deserialize.hpp>
#include <alda/serialization/istream_fwd.hpp>


sanguis::messages::server::unique_ptr
sanguis::messages::server::serialization::deserialize(
	alda::serialization::istream &_stream
)
{
	return
		alda::serialization::deserialize(
			sanguis::messages::server::serialization::global_context(),
			_stream
		);
}
