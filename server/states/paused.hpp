#ifndef SANGUIS_SERVER_STATES_PAUSED_HPP_INCLUDED
#define SANGUIS_SERVER_STATES_PAUSED_HPP_INCLUDED

#include "running.hpp"
#include "../../messages/fwd.hpp"
#include "../../net/types.hpp"

#include <boost/mpl/list.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/result.hpp>
#include <boost/statechart/custom_reaction.hpp>

namespace sanguis
{
namespace server
{

class environment;

namespace states
{

class paused
	: public boost::statechart::simple_state<paused,running>
{
	public:
	typedef boost::mpl::list<
		boost::statechart::custom_reaction<tick_event>,
		boost::statechart::custom_reaction<message_event> 
		> reactions;
	
	// reactions
	boost::statechart::result react(const tick_event&);
	boost::statechart::result react(const message_event&);

	boost::statechart::result operator()(const net::id_type,const messages::disconnect &);
	boost::statechart::result operator()(const net::id_type,const messages::player_unpause &);
	boost::statechart::result operator()(const net::id_type,const messages::player_pause &);
	boost::statechart::result handle_default_msg(const net::id_type,const messages::base &);
};

}
}
}

#endif
