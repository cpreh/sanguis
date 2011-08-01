#ifndef SANGUIS_SERVER_WEAPONS_STATES_BACKSWING_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_STATES_BACKSWING_HPP_INCLUDED

#include "backswing_fwd.hpp"
#include "../weapon.hpp"
#include "../events/poll_fwd.hpp"
#include "../../../diff_timer.hpp"
#include <fcppt/noncopyable.hpp>
#include <boost/statechart/state.hpp>
#include <boost/statechart/result.hpp>
#include <boost/statechart/custom_reaction.hpp>

namespace sanguis
{
namespace server
{
namespace weapons
{
namespace states
{

class backswing
:
	public boost::statechart::state<
		backswing,
		weapon
	>
{
	FCPPT_NONCOPYABLE(
		backswing
	);
public:
	typedef boost::statechart::custom_reaction<
		events::poll
	> reactions;

	explicit backswing(
		my_context
	);

	~backswing();
	
	boost::statechart::result
	react(
		events::poll const &
	);
private:
	sanguis::diff_timer cooldown_;
};

}
}
}
}

#endif
