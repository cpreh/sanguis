#ifndef SANGUIS_SERVER_WEAPONS_EVENTS_POLL_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_EVENTS_POLL_HPP_INCLUDED

#include "poll_fwd.hpp"
#include "../../entities/entity_with_weapon_fwd.hpp"
#include "../../../time_type.hpp"
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
public:
	poll(
		time_type,
		entities::entity_with_weapon &owner);
	
	time_type
	time() const;

	entities::entity_with_weapon &
	owner() const;
private:
	time_type const time_;
	entities::entity_with_weapon &owner_;
};

}
}
}
}

#endif
