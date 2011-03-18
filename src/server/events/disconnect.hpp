#ifndef SANGUIS_SERVER_EVENTS_DISCONNECT_HPP_INCLUDED
#define SANGUIS_SERVER_EVENTS_DISCONNECT_HPP_INCLUDED

#include "disconnect_fwd.hpp"
#include "../../net/id.hpp"
#include <fcppt/nonassignable.hpp>
#include <boost/statechart/event.hpp>

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
