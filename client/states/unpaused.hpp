#ifndef SANGUIS_CLIENT_STATES_UNPAUSED_HPP_INCLUDED
#define SANGUIS_CLIENT_STATES_UNPAUSED_HPP_INCLUDED

#include "running.hpp"
#include "../events/message_fwd.hpp"
#include "../events/menu_fwd.hpp"
#include "../events/tick_fwd.hpp"
#include "../../messages/pause.hpp"
#include <boost/statechart/state.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/result.hpp>
#include <boost/mpl/list.hpp>

namespace sanguis
{
namespace client
{
namespace states
{

class unpaused
:
	public boost::statechart::state<
		unpaused,
		running
	>
{
public:
	typedef boost::mpl::list<
		boost::statechart::custom_reaction<
			events::tick
		>,
		boost::statechart::custom_reaction<
			events::message
		>,
		boost::statechart::custom_reaction<
			events::menu
		>
	> reactions;

	explicit unpaused(
		my_context
	);

	typedef boost::statechart::result result_type;

	boost::statechart::result
	react(
		events::tick const &
	);

	boost::statechart::result
	react(
		events::message const &
	);

	boost::statechart::result
	react(
		events::menu const &
	);

	result_type
	operator()(
		messages::pause const &
	);
private:
	boost::statechart::result
	handle_default_msg(
		messages::base const &
	);
};
}
}
}

#endif
