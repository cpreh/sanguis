#ifndef SANGUIS_CLIENT_EVENTS_MESSAGE_HPP_INCLUDED
#define SANGUIS_CLIENT_EVENTS_MESSAGE_HPP_INCLUDED

#include <sanguis/client/events/message_fwd.hpp>
#include <sanguis/messages/server/shared_ptr.hpp>
#include <sanguis/messages/server/unique_ptr.hpp>
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
		sanguis::client::events::message
	>
{
public:
	explicit
	message(
		sanguis::messages::server::unique_ptr &&
	);

	~message();

	// TODO: Can we get rid of the shared_ptr here?
	sanguis::messages::server::shared_ptr
	value() const;
private:
	sanguis::messages::server::shared_ptr value_;
};

}
}
}

#endif
