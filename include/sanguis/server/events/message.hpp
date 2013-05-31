#ifndef SANGUIS_SERVER_EVENTS_MESSAGE_HPP_INCLUDED
#define SANGUIS_SERVER_EVENTS_MESSAGE_HPP_INCLUDED

#include <sanguis/server/player_id.hpp>
#include <sanguis/server/events/message_fwd.hpp>
#include <sanguis/messages/unique_ptr.hpp>
#include <sanguis/messages/shared_ptr.hpp>
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
		sanguis::messages::unique_ptr &&,
		sanguis::server::player_id
	);

	~message();

	sanguis::messages::shared_ptr const
	get() const;

	sanguis::server::player_id const
	id() const;
private:
	sanguis::messages::shared_ptr const message_;

	sanguis::server::player_id const id_;
};

}
}
}

#endif
