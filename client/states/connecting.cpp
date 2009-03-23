#include "menu.hpp"
#include "connecting.hpp"
#include "running.hpp"
#include "unpaused.hpp"
#include "../log.hpp"
#include "../../dispatch_type.hpp"
#include "../../messages/assign_id.hpp"
#include "../../messages/client_info.hpp"
#include "../../messages/connect.hpp"
#include "../../messages/disconnect.hpp"
#include "../../messages/types.hpp"
#include <sge/renderer/device.hpp>
#include <sge/log/headers.hpp>
#include <sge/iconv.hpp>
#include <sge/text.hpp>
#include <sge/structure_cast.hpp>
#include <sge/font/object.hpp>
#include <sge/font/text_size.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/bind.hpp>
#include <typeinfo>
#include <ostream>

sanguis::client::states::connecting::connecting()
:
	connected(false)
{ 
}

boost::statechart::result
sanguis::client::states::connecting::react(
	message_event const &m)
{
	return dispatch_type<
		boost::mpl::vector<
			messages::assign_id,
			messages::connect,
			messages::disconnect
		>,
		boost::statechart::result>(
		*this,
		*m.message,
		boost::bind(&connecting::handle_default_msg, this, _1));
}

boost::statechart::result
sanguis::client::states::connecting::handle_default_msg(
	messages::base const &m)
{
	SGE_LOG_WARNING(
		log(),
		sge::log::_1
			<< SGE_TEXT("received unexpected message ")
			<< sge::iconv(typeid(m).name()));
	return discard_event();
}

boost::statechart::result
sanguis::client::states::connecting::operator()(
	messages::disconnect const &)
{
	return transit<menu>();
}

boost::statechart::result
sanguis::client::states::connecting::operator()(
	messages::assign_id const &m)
{
	SGE_LOG_DEBUG(
		log(),
		sge::log::_1
			<< SGE_TEXT("received id"));
	post_event(
		message_event(
			messages::auto_ptr(
				new messages::assign_id(
					m))));
	return transit<running>();
}

boost::statechart::result
sanguis::client::states::connecting::operator()(
	messages::connect const &)
{
	context<machine>().send(
		messages::auto_ptr(
			new messages::client_info(
				MESSAGE_TEXT("player1")))); // FIXME
	return discard_event();
}

boost::statechart::result
sanguis::client::states::connecting::react(
	tick_event const &)
{
	machine &m = context<machine>();
	m.dispatch();

	sge::string const status
		= connected
		? SGE_TEXT("waiting for gamestate")
		: SGE_TEXT("connecting");
	
	m.font().draw_text(
		status,
		sge::font::pos::null(),
		sge::structure_cast<
			sge::font::dim
		>(
			m.renderer()->screen_size()),
		sge::font::align_h::center,
		sge::font::align_v::center);

	return discard_event();
}

sge::log::logger &
sanguis::client::states::connecting::log()
{
	static sge::log::logger log_(
		client::log(),
		SGE_TEXT("states::connecting: "),
		true
	);
	return log_;
}
