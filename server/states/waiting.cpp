#include "waiting.hpp"
#include "running.hpp"
#include "unpaused.hpp"
#include "../message_functor.hpp"
#include "../log.hpp"
#include "../entities/entity.hpp"
#include "../../messages/connect.hpp"
#include "../../messages/client_info.hpp"
#include "../../messages/disconnect.hpp"
#include "../../dispatch_type.hpp"

#include <sge/iconv.hpp>
#include <sge/text.hpp>
#include <sge/log/headers.hpp>

#include <boost/bind.hpp>
#include <boost/mpl/vector.hpp>

#include <ostream>

sanguis::server::states::waiting::waiting()
{
	SGE_LOG_DEBUG(
		log(),
		sge::log::_1
			<< SGE_TEXT("constructor"));
}

boost::statechart::result
sanguis::server::states::waiting::react(
	tick_event const &) 
{
	return discard_event();
}

boost::statechart::result
sanguis::server::states::waiting::operator()(
	net::id_type const id,
	messages::connect const &m)
{
	SGE_LOG_INFO(
		log(),
		sge::log::_1
			<< SGE_TEXT("received client with id ")
			<< id);
	return discard_event();
}

boost::statechart::result
sanguis::server::states::waiting::operator()(
	net::id_type const id,
	messages::disconnect const &)
{
	SGE_LOG_INFO(
		log(),
		sge::log::_1
			<< SGE_TEXT("client ")
			<< id
			<< SGE_TEXT(" disconnected"));
	return discard_event();
}

boost::statechart::result
sanguis::server::states::waiting::operator()(
	net::id_type const id,
	messages::client_info const &m)
{
	post_event(
		message_event(
			messages::auto_ptr(
				new messages::client_info(m)),
			id));
	return transit<running>();
}

boost::statechart::result
sanguis::server::states::waiting::handle_default_msg(
	net::id_type,
	messages::base const &m)
{
	SGE_LOG_WARNING(
		log(),
		sge::log::_1
			<< SGE_TEXT("got unexpected message ")
			<< sge::iconv(typeid(m).name()));
	return discard_event();
}

boost::statechart::result
sanguis::server::states::waiting::react(
	message_event const &m) 
{
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

sge::log::logger &
sanguis::server::states::waiting::log()
{
	static sge::log::logger log_(
		server::log(),
		SGE_TEXT("waiting: "));
	return log_;
}
