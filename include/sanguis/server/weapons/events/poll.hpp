#ifndef SANGUIS_SERVER_WEAPONS_EVENTS_POLL_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_EVENTS_POLL_HPP_INCLUDED

#include <sanguis/server/weapons/events/poll_fwd.hpp>
#include <sanguis/server/entities/with_weapon_fwd.hpp>
#include <fcppt/nonassignable.hpp>
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

class poll
:
	public boost::statechart::event<
		sanguis::server::weapons::events::poll
	>
{
	FCPPT_NONASSIGNABLE(
		poll
	);
public:
	explicit
	poll(
		sanguis::server::entities::with_weapon &owner
	);

	sanguis::server::entities::with_weapon &
	owner() const;
private:
	sanguis::server::entities::with_weapon &owner_;
};

}
}
}
}

#endif
