#include "paused.hpp"
#include "unpaused.hpp"
#include "waiting.hpp"
#include "../message_functor.hpp"
#include "../entities/entity.hpp"
#include "../../log_headers.hpp"
#include "../../dispatch_type.hpp"
#include "../../messages/unpause.hpp"
#include "../../messages/player_pause.hpp"
#include "../../messages/player_unpause.hpp"
#include "../../messages/disconnect.hpp"

#include <sge/iconv.hpp>

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

boost::statechart::result
sanguis::server::states::paused::operator()(
	net::id_type const id,
	messages::disconnect const &)
{
	if (context<running>().players().find(id) == context<running>().players().end())
	{
		SGE_LOG_INFO(
			log(),
			sge::log::_1
				<< SGE_TEXT("spectator ")
				<< id
				<< SGE_TEXT(" disconnected"));
		return discard_event();
	}

	SGE_LOG_INFO(
		log(),
		sge::log::_1
			<< SGE_TEXT("client with id ")
			<< id
			<< SGE_TEXT(" disconnected"));
	return transit<waiting>();
}

boost::statechart::result
sanguis::server::states::paused::operator()(
	net::id_type,
	messages::player_unpause const &)
{
	context<running>().get_environment().send(
		messages::auto_ptr(
			new messages::unpause()));
	return transit<unpaused>();
}

boost::statechart::result
sanguis::server::states::paused::operator()(
	net::id_type,
	messages::player_pause const &)
{
	SGE_LOG_WARNING(
		log(),
		sge::log::_1
			<< SGE_TEXT("server: got superfluous pause"));;
	return discard_event();
}

boost::statechart::result sanguis::server::states::paused::handle_default_msg(const net::id_type,const messages::base &m)
{
	SGE_LOG_WARNING(
		log(),
		sge::log::_1
			<< SGE_TEXT("server: got invalid event ")
			<< sge::iconv(typeid(m).name()));
	return discard_event();
}
