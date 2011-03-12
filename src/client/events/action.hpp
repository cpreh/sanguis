#ifndef SANGUIS_CLIENT_EVENTS_ACTION_HPP_INCLUDED
#define SANGUIS_CLIENT_EVENTS_ACTION_HPP_INCLUDED

#include "action_fwd.hpp"
#include "../control/player_action.hpp"
#include <fcppt/nonassignable.hpp>
#include <boost/statechart/event.hpp>

namespace sanguis
{
namespace client
{
namespace events
{

class action
:
	public boost::statechart::event<
		action
	>
{
	FCPPT_NONASSIGNABLE(
		action
	)
public:
	explicit action(
		control::player_action const &
	);

	control::player_action
	value() const;
private:
	control::player_action const value_;
};

}
}
}

#endif
