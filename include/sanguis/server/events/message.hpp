#ifndef SANGUIS_SERVER_EVENTS_MESSAGE_HPP_INCLUDED
#define SANGUIS_SERVER_EVENTS_MESSAGE_HPP_INCLUDED

#include <sanguis/server/events/message_fwd.hpp>
#include <sanguis/messages/auto_ptr.hpp>
#include <sanguis/messages/shared_ptr.hpp>
#include <alda/net/id.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/event.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
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
	message(
		sanguis::messages::auto_ptr,
		alda::net::id
	);

	~message();

	sanguis::messages::shared_ptr const
	get() const;

	alda::net::id const
	id() const;
private:
	sanguis::messages::shared_ptr const message_;

	alda::net::id const id_;
};

}
}
}

#endif
