#ifndef SANGUIS_SERVER_WEAPONS_EVENTS_POLL_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_EVENTS_POLL_HPP_INCLUDED

#include "poll_fwd.hpp"
#include "../../entities/with_weapon_fwd.hpp"
#include <fcppt/nonassignable.hpp>
#include <boost/statechart/event.hpp>

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
		poll
	>
{
	FCPPT_NONASSIGNABLE(
		poll
	);
public:
	explicit poll(
		entities::with_weapon &owner
	);

	entities::with_weapon &
	owner() const;
private:
	entities::with_weapon &owner_;
};

}
}
}
}

#endif
