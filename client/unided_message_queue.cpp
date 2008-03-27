#include "unided_message_queue.hpp"
#include <sge/exception.hpp>
#include <utility>
#include <cassert>

const sge::string sanguis::client::unided_message_queue::no_name(SGE_TEXT(""));

sanguis::client::unided_message_queue::unided_message_queue()
: messages_to_defer_(0)
{}

void sanguis::client::unided_message_queue::defer(
	message_ptr_in msg,
	sge::string const& name)
{
	messages.push_back(msg);
	if(name != no_name
	&& ids.insert(std::make_pair(name, invalid_id)).second == false)
		throw sge::exception(SGE_TEXT("Unique identifier used twice in unided_message_queue!"));
	name_queue.push(name);
	++messages_to_defer_;
}

sanguis::client::unided_message_queue::message_ptr_out
sanguis::client::unided_message_queue::next(const entity_id id)
{
	if(messages.empty())
		throw sge::exception(SGE_TEXT("unided_message_queue::next(): queue is empty!"));

	assert(!name_queue.empty());
	sge::string const &name(name_queue.front());
	if(name != no_name)
	{
		const name_id_map::iterator it = ids.find(name);
		assert(it == ids.end());
		it->second = id;
	}
	messages.front().id(id);
	return messages.pop_front();
}

sanguis::entity_id
sanguis::client::unided_message_queue::get_id(
	sge::string const& name) const
{
	const name_id_map::const_iterator it(ids.find(name));
	if(it == ids.end())
		throw sge::exception(SGE_TEXT("id is not assigned in unided_message_queue!"));
	return it->second;
}

sanguis::client::unided_message_queue::size_type
sanguis::client::unided_message_queue::messages_to_defer()
{
	const size_type temp = messages_to_defer_;
	messages_to_defer_ = 0;
	return temp;
}
