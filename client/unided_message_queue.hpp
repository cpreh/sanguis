#ifndef SANGUIS_UNIDED_MESSAGE_QUEUE_HPP_INCLUDED
#define SANGUIS_UNIDED_MESSAGE_QUEUE_HPP_INCLUDED

#include "../messages/entity_message.hpp"
#include <sge/string.hpp>
#include <boost/ptr_container/ptr_deque.hpp>
#include <map>
#include <memory>
#include <queue>

namespace sanguis
{
namespace client
{

class unided_message_queue {
	typedef boost::ptr_deque<
		messages::entity_message> message_queue;
public:
	// TODO: probably use message_ptr everywhere
	//       and put messages and name_queue together
	// TODO: maybe assign unique client ids automatically and use int instead
	typedef std::auto_ptr<messages::entity_message> message_ptr_in;
	typedef message_queue::size_type size_type;
	typedef message_queue::auto_type message_ptr_out;

	static const sge::string no_name;

	unided_message_queue();
	void defer(message_ptr_in, sge::string const& name = no_name);
	message_ptr_out next(entity_id new_id);
	entity_id get_id(sge::string const& name) const;

	size_type messages_to_defer();
private:
	size_type     messages_to_defer_;
	message_queue messages;
	typedef std::map<
		sge::string,
		entity_id> name_id_map;
	name_id_map ids;
	std::queue<sge::string> name_queue;
};

}
}

#endif
