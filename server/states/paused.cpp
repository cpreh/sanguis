#include "paused.hpp"
#include "unpaused.hpp"
#include "waiting.hpp"
#include "../message_functor.hpp"
#include "../../dispatch_type.hpp"
#include "../../messages/unpause.hpp"
#include "../../messages/player_pause.hpp"
#include "../../messages/player_unpause.hpp"
#include "../../messages/disconnect.hpp"
#include "../entities/entity.hpp"

#include <sge/iostream.hpp>

#include <boost/bind.hpp>
#include <boost/mpl/vector.hpp>

#include <typeinfo>
#include <ostream>

// reactions
boost::statechart::result sanguis::server::states::paused::react(const tick_event&)
{
	return discard_event();
}

boost::statechart::result sanguis::server::states::paused::react(const message_event&m)
{
	message_functor<paused,boost::statechart::result> mf(*this,m.id);

	return dispatch_type<
		boost::mpl::vector<
			messages::disconnect,
			messages::player_pause,
			messages::player_unpause
		>,
		boost::statechart::result>(
			mf,
			*m.message,
			boost::bind(&paused::handle_default_msg, this, m.id, _1));
}

boost::statechart::result sanguis::server::states::paused::operator()(const net::id_type id,const messages::disconnect &)
{
	if (context<running>().players().find(id) == context<running>().players().end())
	{
		sge::clog << SGE_TEXT("server: spectator ") << id << SGE_TEXT(" disconnected\n");
		return discard_event();
	}

	sge::clog << SGE_TEXT("server: disconnected\n");
	return transit<waiting>();
}

boost::statechart::result sanguis::server::states::paused::operator()(const net::id_type,const messages::player_unpause &)
{
	sge::cout << SGE_TEXT("server: unpausing\n");
	context<running>().get_environment().send(
		messages::auto_ptr(
			new messages::unpause()));
	return transit<unpaused>();
}

boost::statechart::result sanguis::server::states::paused::operator()(const net::id_type,const messages::player_pause &)
{
	sge::cout << SGE_TEXT("server: got superfluous pause\n");
	return discard_event();
}

boost::statechart::result sanguis::server::states::paused::handle_default_msg(const net::id_type,const messages::base &m)
{
	sge::cout << SGE_TEXT("server: got invalid event ") << typeid(m).name() << SGE_TEXT("\n");
	return discard_event();
}
