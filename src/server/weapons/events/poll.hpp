#ifndef SANGUIS_SERVER_WEAPONS_EVENTS_POLL_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_EVENTS_POLL_HPP_INCLUDED

#include "poll_fwd.hpp"
#include "../../entities/with_weapon_fwd.hpp"
#include "../../../time_delta.hpp"
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
	poll(
		sanguis::time_delta const &,
		entities::with_weapon &owner
	);
	
	sanguis::time_delta const &
	time() const;

	entities::with_weapon &
	owner() const;
private:
	sanguis::time_delta const time_;

	entities::with_weapon &owner_;
};

}
}
}
}

#endif
