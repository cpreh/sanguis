#ifndef SANGUIS_CLIENT_START_STATE_HPP_INCLUDED
#define SANGUIS_CLIENT_START_STATE_HPP_INCLUDED

#include "machine.hpp"
#include "../tick_event.hpp"
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/result.hpp>

namespace sanguis
{
namespace client
{

// TODO: use this state as a state inbetween two others to 
// reset configuration (using the statechart history maybe)
struct start_state
	: public boost::statechart::simple_state<start_state,machine>
{
	typedef boost::statechart::custom_reaction<tick_event> reactions;

	start_state();
	boost::statechart::result react(const tick_event&);
};
}
}

#endif
