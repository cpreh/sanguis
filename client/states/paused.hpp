#ifndef SANGUIS_CLIENT_STATES_PAUSED_HPP_INCLUDED
#define SANGUIS_CLIENT_STATES_PAUSED_HPP_INCLUDED

#include "running.hpp"
#include "../perk_chooser.hpp"
#include "../events/message_fwd.hpp"
#include "../events/tick_fwd.hpp"
#include "../../messages/unpause.hpp"
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
class paused
:
	public boost::statechart::state<
		paused,
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
		>
	> reactions;

	explicit paused(
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

	result_type
	operator()(
		messages::unpause const &
	);
private:
	boost::statechart::result
	handle_default_msg(
		messages::base const &
	);

	perk_chooser::activation chooser_activation_;
};
}
}
}

#endif
