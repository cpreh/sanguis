#include "deserialize.hpp"
#include "context.hpp"
#include "reader.hpp"
#include "dispatcher_base.hpp"
#include "../base.hpp"
#include "../types/message_type.hpp"
#include "../../exception.hpp"
#include <sge/text.hpp>
#include <sge/cerr.hpp>
#include <boost/static_assert.hpp>

sanguis::messages::auto_ptr
sanguis::messages::serialization::deserialize(
	context const &ctx,
	istream &stream)
{
	types::message_type type;

	// TODO: we can't specify the endianness of the message type at the moment
	BOOST_STATIC_ASSERT(sizeof(types::message_type) == 1);

	sge::cerr << "-----------------TYPE IS: " << int(type) << "\n";

	// TODO: fix endianness here
	stream.read(
		reinterpret_cast<char *>(&type), sizeof(type)
	);

	if(type > types::message::size_)
		throw exception(
			SGE_TEXT("Invalid message received!")
		);

	types::message::type const casted_type(
		static_cast<types::message::type>(type)
	);

	dispatch_map::const_iterator const it = ctx.handlers().find(casted_type);

	if(it == ctx.handlers().end())
		throw exception(
			SGE_TEXT("No handler for a message found.")
		);
	
	reader d(stream);

	return it->second->on_dispatch(d);
}
