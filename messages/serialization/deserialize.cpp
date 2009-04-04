#include "deserialize.hpp"
#include "context.hpp"
#include "reader.hpp"
#include "dispatcher_base.hpp"
#include "../base.hpp"
#include "../types/message.hpp"
#include "../../exception.hpp"
#include <sge/text.hpp>

#include <sge/cerr.hpp>

sanguis::messages::auto_ptr
sanguis::messages::serialization::deserialize(
	context const &ctx,
	istream &stream)
{
	types::message::type t;

	// TODO: fix endianness here
	stream.read(
		reinterpret_cast<char *>(&t), sizeof(t)
	);

	dispatch_map::const_iterator const it = ctx.handlers().find(t);

	if(it == ctx.handlers().end())
		throw exception(
			SGE_TEXT("Invalid message received.")
		);
	
	reader d(stream);

	return it->second->on_dispatch(d);
}
