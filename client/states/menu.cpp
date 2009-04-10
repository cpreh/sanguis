#include "menu.hpp"
#include "connecting.hpp"
#include "../../media_path.hpp"
#include "../../messages/base.hpp"
#include "../machine.hpp"
#include "../log.hpp"
#include <sge/log/headers.hpp>
#include <sge/font/object.hpp>
#include <sge/font/text_size.hpp>
#include <sge/renderer/device.hpp>
#include <sge/image/loader.hpp>
#include <sge/gui/skins/standard.hpp>
#include <sge/gui/make_image.hpp>
#include <sge/gui/layouts/vertical.hpp>
#include <sge/gui/layouts/horizontal.hpp>
#include <sge/systems/instance.hpp>
#include <sge/text.hpp>
#include <sge/cerr.hpp>
#include <sge/iconv.hpp>
#include <sge/make_shared_ptr.hpp>
#include <sge/structure_cast.hpp>
#include <sge/lexical_cast.hpp>
#include <boost/ref.hpp>
#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <ostream>

sanguis::client::states::menu::menu(
	my_context ctx) 
:
	my_base(ctx),
	menu_(
		context<machine>().sys(),
		sanguis::menu::callbacks::object(
			boost::bind(
				&menu::connect,
				this,
				_1,
				_2),
			boost::bind(
				&menu::cancel_connect,
				this),
			boost::bind(
				&machine::start_server,
				&(context<machine>()))))
{}

boost::statechart::result
sanguis::client::states::menu::react(
	tick_event const &t)
{
	context<machine>().dispatch();

	menu_.process(
		t.delta())

	return discard_event();
}


boost::statechart::result
sanguis::client::states::menu::react(
	message_event const &m)
{
	return messages::unwrap<
		boost::mpl::vector<
			messages::assign_id,
			messages::connect,
			messages::disconnect,
			messages::net_error
		>,
		boost::statechart::result
	>(
		*this,
		*m.message(),
		boost::bind(
			&menu::handle_default_msg,
			this,
			_1
		)
	);
}

boost::statechart::result
sanguis::client::states::running::handle_default_msg(
	messages::base const &m)
{
	SGE_LOG_WARNING(
		log(),
		sge::log::_1
			<< SGE_TEXT("got unexpected event ")
			<< sge::iconv(typeid(*m.message()).name()));
	return discard_event();
}

boost::statechart::result
sanguis::client::states::running::operator()(
	messages::net_error const &e)
{
	menu_.connection_error(
		e.message());
	return discard_event();
}

boost::statechart::result
sanguis::client::states::running::operator()(
	messages::connect const &c)
{
	followup_state_ = c.state();
	context<machine>().send(
		messages::create(
			messages::client_info(
				SGE_TEXT("player1")
			)
		)
	); // FIXME
	return discard_event();
}

boost::statechart::result
sanguis::client::states::running::operator()(
	messages::disconnect const &c)
{
	menu_.connection_error(
		SGE_TEXT("The server closed the connection"));
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
			messages::create(
				messages::assign_id(
					m
				)
			)
		)
	);
	switch (followup_state_)
	{
		case followup_state::unpaused:
			return transit<unpaused>();
		case followup_state::paused
			return transit<paused>();
	}
	throw sge::exception(
		SGE_TEXT("invalid followup state!"));
}

sge::log::logger &
sanguis::client::states::menu::log()
{
	static sge::log::logger log_(
		client::log(),
		SGE_TEXT("states::menu: "),
		true
	);
	return log_;
}

void sanguis::client::states::menu::connect(
	sge::string const &host,
	sge::string const &port)
{
	context<machine>().hostname(
		sge::iconv(
			host
		)
	);

	try
	{
		context<machine>().port(
			sge::lexical_cast<net::port_type>(
				port));
	}
	catch (sge::bad_lexical_cast const &)
	{
		menu_.connection_error(
			SGE_TEXT("invalid port specification"));
	}

	context<machine>().connect();
}

void sanguis::client::states::menu::start_server()
{
	context<machine>().start_server();
}

void sanguis::client::states::menu::cancel_connect()
{
	context<machine>().cancel_connect();
}
