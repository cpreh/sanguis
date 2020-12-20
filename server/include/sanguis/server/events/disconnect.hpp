#ifndef SANGUIS_SERVER_EVENTS_DISCONNECT_HPP_INCLUDED
#define SANGUIS_SERVER_EVENTS_DISCONNECT_HPP_INCLUDED

#include <sanguis/server/events/disconnect_fwd.hpp>
#include <alda/net/id.hpp>
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
public:
	explicit
	disconnect(
		alda::net::id
	);

	disconnect(
		disconnect &&
	)
	noexcept;

	disconnect(
		disconnect const &
	);

	disconnect &
	operator=(
		disconnect &&
	)
	noexcept;

	disconnect &
	operator=(
		disconnect const &
	);

	~disconnect()
	override;

	[[nodiscard]]
	alda::net::id
	id() const;
private:
	alda::net::id id_;
};

}
}
}

#endif
