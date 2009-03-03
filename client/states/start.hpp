#ifndef SANGUIS_CLIENT_STATES_START_HPP_INCLUDED
#define SANGUIS_CLIENT_STATES_START_HPP_INCLUDED

#include "../machine.hpp"
#include "../../tick_event.hpp"
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/result.hpp>

namespace sanguis
{
namespace client
{

namespace states
{
// TODO: use this state as a state inbetween two others to 
// reset configuration (using the statechart history maybe)
class start
	: public boost::statechart::simple_state<start,machine>
{
	public:
	typedef boost::statechart::custom_reaction<tick_event> reactions;

	start();
	boost::statechart::result react(const tick_event&);
};
}
}
}

#endif
