#include "deserialize.hpp"
#include "context.hpp"
#include "reader.hpp"
#include "dispatcher_base.hpp"
#include "../base.hpp"
#include "../types/message_type.hpp"
#include "../../exception.hpp"
#include <fcppt/assert.hpp>
#include <fcppt/text.hpp>
#include <boost/static_assert.hpp>

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

	FCPPT_ASSERT(
		static_cast<
			std::size_t
		>(
			_stream.gcount()
		)
		== 
		sizeof(types::message_type)
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
