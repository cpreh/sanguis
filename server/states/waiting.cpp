#include "waiting.hpp"
#include "running.hpp"
#include "unpaused.hpp"
#include "../../messages/connect.hpp"
#include "../../messages/client_info.hpp"
#include "../../messages/disconnect.hpp"
#include "../../dispatch_type.hpp"
#include "../message_functor.hpp"
#include "../entities/entity.hpp"

#include <sge/iostream.hpp>
#include <sge/string.hpp>

#include <boost/bind.hpp>
#include <boost/mpl/vector.hpp>

sanguis::server::states::waiting::waiting()
{
	sge::clog << SGE_TEXT("server: entering waiting state\n");
}

boost::statechart::result sanguis::server::states::waiting::react(const tick_event&) 
{
	return discard_event();
}

boost::statechart::result sanguis::server::states::waiting::operator()(const net::id_type id,const messages::connect &)
{
	sge::clog << SGE_TEXT("server: received client with id ") << id << SGE_TEXT("\n");
	return discard_event();
}

boost::statechart::result sanguis::server::states::waiting::operator()(const net::id_type id,const messages::disconnect &)
{
	sge::clog << SGE_TEXT("server: client ") << id << SGE_TEXT(" disconnected\n");
	return discard_event();
}

boost::statechart::result sanguis::server::states::waiting::operator()(const net::id_type id,const messages::client_info &m)
{
	sge::clog << SGE_TEXT("server: received client info from id ") << id << SGE_TEXT("\n");

	//post_event(message_event(message_ptr(new messages::client_info(m)),id));
	post_event(message_event(message_ptr(new messages::client_info(m)),id));
	return transit<running>();
}

boost::statechart::result sanguis::server::states::waiting::handle_default_msg(const net::id_type,const messages::base &m)
{
	sge::clog << SGE_TEXT("server: got unexpected message ") << typeid(m).name() << SGE_TEXT("\n");
	return discard_event();
}

boost::statechart::result sanguis::server::states::waiting::react(const message_event&m) 
{
	sge::clog << "server: react with " << m.id << "\n";
	message_functor<waiting,boost::statechart::result> mf(*this,m.id);
	return dispatch_type<
		boost::mpl::vector<
			messages::connect,
			messages::disconnect,
			messages::client_info
		>,
		boost::statechart::result>(
		mf,
		*m.message,
		boost::bind(&waiting::handle_default_msg,this,m.id,_1));
}


