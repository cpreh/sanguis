#include "waiting_state.hpp"
#include "running_state.hpp"
#include "../messages/connect.hpp"
#include "../messages/client_info.hpp"
#include "../messages/disconnect.hpp"
#include "../dispatch_type.hpp"
#include "message_functor.hpp"

#include <sge/iostream.hpp>
#include <sge/string.hpp>

#include <boost/bind.hpp>
#include <boost/mpl/vector.hpp>

sanguis::server::waiting_state::waiting_state() 
{
	sge::clog << SGE_TEXT("server: entering waiting state\n");
}

boost::statechart::result sanguis::server::waiting_state::react(const tick_event&) 
{
	return discard_event();
}

boost::statechart::result sanguis::server::waiting_state::operator()(const net::id_type,const messages::connect &)
{
	sge::clog << SGE_TEXT("server: received client\n");
	return discard_event();
}

boost::statechart::result sanguis::server::waiting_state::operator()(const net::id_type,const messages::disconnect &)
{
	sge::clog << SGE_TEXT("server: disconnected again\n");
	return discard_event();
}

boost::statechart::result sanguis::server::waiting_state::operator()(const net::id_type id,const messages::client_info &m)
{
	sge::clog << SGE_TEXT("server: received client info\n");
	post_event(message_event(message_ptr(new messages::client_info(m)),id));
	return transit<running_state>();
}

boost::statechart::result sanguis::server::waiting_state::handle_default_msg(const net::id_type,const messages::base &m)
{
	sge::clog << SGE_TEXT("server: got unexpected message ") << typeid(m).name() << SGE_TEXT("\n");
	return discard_event();
}

boost::statechart::result sanguis::server::waiting_state::react(const message_event&m) 
{
	message_functor<waiting_state> mf(*this,m.id);
	return dispatch_type<
		boost::mpl::vector<
			messages::connect,
			messages::disconnect,
			messages::client_info
		>,
		boost::statechart::result>(
		mf,
		*m.message,
		boost::bind(&waiting_state::handle_default_msg,this,m.id,_1));
}


