#ifndef SANGUIS_CLIENT_STATES_INTERMEDIATE_HPP_INCLUDED
#define SANGUIS_CLIENT_STATES_INTERMEDIATE_HPP_INCLUDED

#include "../machine.hpp"
#include "../../tick_event.hpp"
#include "../message_event.hpp"
#include <sge/log/fwd.hpp>
#include <boost/statechart/state.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/mpl/list.hpp>

namespace sanguis
{
namespace client
{
namespace states
{
class intermediate 
	: public boost::statechart::state<intermediate,machine>
{
	public:
	typedef boost::mpl::list<
		boost::statechart::custom_reaction<tick_event>,
		boost::statechart::custom_reaction<message_event>
		> reactions;

	intermediate(my_context); 
	boost::statechart::result react(tick_event const &);
	boost::statechart::result react(message_event const &);
	private:
	sge::log::logger &log();
};
}
}
}

#endif
