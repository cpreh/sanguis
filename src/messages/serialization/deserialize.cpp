#include <sanguis/messages/serialization/deserialize.hpp>
#include <sanguis/messages/serialization/context.hpp>
#include <sanguis/messages/serialization/dispatcher_base.hpp>
#include <sanguis/messages/serialization/reader.hpp>
#include <sanguis/messages/types/message_type.hpp>
#include <sanguis/messages/base.hpp>
#include <sanguis/exception.hpp>
#include <fcppt/assert/throw.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/static_assert.hpp>
#include <fcppt/config/external_end.hpp>

sanguis::messages::auto_ptr
sanguis::messages::serialization::deserialize(
	context const &_ctx,
	istream &_stream
)
{
	types::message_type type;

	// TODO: we can't specify the endianness of the message type at the moment
	BOOST_STATIC_ASSERT(
		sizeof(types::message_type) == 1
	);

	// TODO: fix endianness here
	_stream.read(
		reinterpret_cast<
			char *
		>(
			&type
		),
		sizeof(type)
	);

	FCPPT_ASSERT_THROW(
		static_cast<
			std::size_t
		>(
			_stream.gcount()
		)
		==
		sizeof(types::message_type),
		sanguis::exception
	);

	_stream.unget();

	if(
		type >= types::message::size
	)
		throw sanguis::exception(
			FCPPT_TEXT("Invalid message received!")
		);

	types::message::type const casted_type(
		static_cast<
			types::message::type
		>(
			type
		)
	);

	dispatch_map::const_iterator const it(
		_ctx.handlers().find(
			casted_type
		)
	);

	if(
		it == _ctx.handlers().end()
	)
		throw sanguis::exception(
			FCPPT_TEXT("No handler for a message found.")
		);

	serialization::reader cur_reader(
		_stream
	);

	return
		it->second->on_dispatch(
			cur_reader
		);
}
