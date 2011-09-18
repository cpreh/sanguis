#ifndef SANGUIS_SERVER_EVENTS_DISCONNECT_HPP_INCLUDED
#define SANGUIS_SERVER_EVENTS_DISCONNECT_HPP_INCLUDED

#include <sanguis/server/events/disconnect_fwd.hpp>
#include <sanguis/net/id.hpp>
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

class disconnect
:
	public boost::statechart::event<
		disconnect
	>
{
	FCPPT_NONASSIGNABLE(
		disconnect
	);
public:
	explicit disconnect(
		net::id
	);

	net::id
	id() const;
private:
	net::id const id_;
};

}
}
}

#endif
