#ifndef SANGUIS_SERVER_EVENTS_MESSAGE_HPP_INCLUDED
#define SANGUIS_SERVER_EVENTS_MESSAGE_HPP_INCLUDED

#include <sanguis/server/player_id.hpp>
#include <sanguis/server/events/message_fwd.hpp>
#include <sanguis/messages/client/unique_ptr.hpp>
#include <sanguis/messages/client/shared_ptr.hpp>
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
public:
	message(
		sanguis::messages::client::unique_ptr &&,
		sanguis::server::player_id
	);

	~message();

	sanguis::messages::client::shared_ptr
	get() const;

	sanguis::server::player_id const
	id() const;
private:
	sanguis::messages::client::shared_ptr message_;

	sanguis::server::player_id id_;
};

}
}
}

#endif
