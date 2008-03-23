#ifndef SANGUIS_SERVER_WAITING_STATE_HPP_INCLUDED
#define SANGUIS_SERVER_WAITING_STATE_HPP_INCLUDED

#include "machine.hpp"
#include "message_event.hpp"
#include "../tick_event.hpp"

#include "../messages/fwd.hpp"

#include <boost/mpl/list.hpp>
#include <boost/statechart/simple_state.hpp>
#include <boost/statechart/custom_reaction.hpp>
#include <boost/statechart/result.hpp>

namespace sanguis
{
namespace server
{

struct waiting_state
	: public boost::statechart::simple_state<waiting_state,machine>
{
	typedef boost::mpl::list<
		boost::statechart::custom_reaction<tick_event>,
		boost::statechart::custom_reaction<message_event> 
		> reactions;

	waiting_state();
	boost::statechart::result react(const tick_event&);
	boost::statechart::result react(const message_event&);

	boost::statechart::result operator()(const net::id_type,const messages::connect &);
	boost::statechart::result operator()(const net::id_type,const messages::disconnect &);
	boost::statechart::result operator()(const net::id_type,const messages::client_info &);
	boost::statechart::result handle_default_msg(const net::id_type,const messages::base &);
};


}
}

#endif
