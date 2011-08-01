#ifndef SANGUIS_SERVER_WEAPONS_STATES_RELOADING_HPP_INCLUDED
#define SANGUIS_SERVER_WEAPONS_STATES_RELOADING_HPP_INCLUDED

#include "reloading_fwd.hpp"
#include "../weapon.hpp"
#include "../events/poll_fwd.hpp"
#include "../events/stop_fwd.hpp"
#include "../events/reset_fwd.hpp"
#include "../../../diff_timer.hpp"
#include <fcppt/noncopyable.hpp>
#include <boost/statechart/state.hpp>
#include <boost/statechart/result.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/mpl/list.hpp>

namespace sanguis
{
namespace server
{
namespace weapons
{
namespace states
{

class reloading
:
	public boost::statechart::state<
		reloading,
		weapon
	>
{
	FCPPT_NONCOPYABLE(
		reloading
	);
public:
	typedef boost::mpl::list<
		boost::statechart::custom_reaction<
			events::poll
		>,
		boost::statechart::custom_reaction<
			events::stop
		>,
		boost::statechart::custom_reaction<
			events::reset
		>
	> reactions;

	explicit reloading(
		my_context
	);

	~reloading();
	
	boost::statechart::result
	react(
		events::poll const &
	);

	boost::statechart::result
	react(
		events::stop const &
	);
	
	boost::statechart::result
	react(
		events::reset const &
	);
private:
	sanguis::diff_timer reload_time_;
};

}
}
}
}

#endif
