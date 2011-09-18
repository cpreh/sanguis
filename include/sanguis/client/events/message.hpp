#ifndef SANGUIS_CLIENT_EVENTS_MESSAGE_HPP_INCLUDED
#define SANGUIS_CLIENT_EVENTS_MESSAGE_HPP_INCLUDED

#include <sanguis/client/events/message_fwd.hpp>
#include <sanguis/messages/auto_ptr.hpp>
#include <sanguis/messages/shared_ptr.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/event.hpp>
#include <fcppt/config/external_end.hpp>

namespace sanguis
{
namespace client
{
namespace events
{

class message
:
	public boost::statechart::event<
		message
	>
{
	FCPPT_NONASSIGNABLE(
		message
	);
public:
	explicit message(
		messages::auto_ptr message
	);

	~message();

	messages::shared_ptr const
	value() const;
private:
	messages::shared_ptr const value_;
};

}
}
}

#endif
