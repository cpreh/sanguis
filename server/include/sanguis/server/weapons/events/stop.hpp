#ifndef SANGUIS_SERVER_WEAPONS_EVENTS_STOP_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_EVENTS_STOP_HPP_INCLUDED

#include <sanguis/server/weapons/events/stop_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/event.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
{
namespace weapons
{
namespace events
{

class stop
:
	public boost::statechart::event<
		sanguis::server::weapons::events::stop
	>
{
public:
	stop();

	stop(
		stop &&
	);

	stop(
		stop const &
	);

	stop &
	operator=(
		stop &&
	);

	stop &
	operator=(
		stop const &
	);

	~stop()
	override;
};

}
}
}
}

#endif
