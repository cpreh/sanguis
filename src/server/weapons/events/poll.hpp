#ifndef SANGUIS_SERVER_WEAPONS_EVENTS_POLL_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_EVENTS_POLL_HPP_INCLUDED

#include "poll_fwd.hpp"
#include "../../entities/with_weapon_fwd.hpp"
#include "../../../time_type.hpp"
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
	)
public:
	poll(
		time_type,
		entities::with_weapon &owner
	);
	
	time_type
	time() const;

	entities::with_weapon &
	owner() const;
private:
	time_type const time_;

	entities::with_weapon &owner_;
};

}
}
}
}

#endif
