#ifndef SANGUIS_CLIENT_EVENTS_MESSAGE_HPP_INCLUDED
#define SANGUIS_CLIENT_EVENTS_MESSAGE_HPP_INCLUDED

#include "message_fwd.hpp"
#include "../../messages/auto_ptr.hpp"
#include "../../messages/shared_ptr.hpp"
#include <boost/statechart/event.hpp>

namespace sanguis
{
namespace client
{
namespace events
{

struct message
:
	boost::statechart::event<
		message
	>
{
	explicit message(
		messages::auto_ptr message
	);
	
	~message();

	messages::shared_ptr const
	value() const;
private:
	messages::shared_ptr value_;
};

}
}
}

#endif
