#include <sanguis/messages/base.hpp>
#include <sanguis/messages/unique_ptr.hpp>
#include <sanguis/messages/serialization/context_fwd.hpp>
#include <sanguis/messages/serialization/deserialize.hpp>
#include <alda/serialization/deserialize.hpp>
#include <alda/serialization/istream.hpp>


sanguis::messages::unique_ptr
sanguis::messages::serialization::deserialize(
	sanguis::messages::serialization::context const &_ctx,
	alda::serialization::istream &_stream
)
{
	return
		alda::serialization::deserialize(
			_ctx,
			_stream
		);
}
