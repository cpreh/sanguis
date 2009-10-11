#include "menu.hpp"
#include "paused.hpp"
#include "unpaused.hpp"
#include "../../messages/base.hpp"
#include "../../messages/unwrap.hpp"
#include "../../messages/create.hpp"
#include "../../messages/client_info.hpp"
#include "../machine.hpp"
#include "../message_event.hpp"
#include "../menu_event.hpp"
#include "../log.hpp"
#include <sge/log/headers.hpp>
#include <sge/log/parameters/inherited.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/image/colors.hpp>
#include <sge/utf8/convert.hpp>
#include <sge/lexical_cast.hpp>
#include <sge/text.hpp>
#include <sge/iconv.hpp>
#include <boost/mpl/vector.hpp>
#include <tr1/functional>
#include <ostream>

sanguis::client::states::menu::menu(
	my_context ctx) 
:
	my_base(ctx),
	menu_(
		context<machine>().sys(),
		context<machine>().cursor(),
		client::menu::callbacks::object(
			std::tr1::bind(
				&menu::connect,
				this,
				std::tr1::placeholders::_1,
				std::tr1::placeholders::_2
			),
			std::tr1::bind(
				&menu::cancel_connect,
				this
			),
			std::tr1::bind(
				&machine::start_server,
				&context<machine>()
			),
			std::tr1::bind(
				&machine::quit,
				&context<machine>()
			)
		)
	),
	connect_state_(),
	renderer_state_(
		context<machine>().renderer(),
		sge::renderer::state::list
			(sge::renderer::state::bool_::clear_backbuffer = true)
			(sge::renderer::state::bool_::clear_zbuffer = false)
			(sge::renderer::state::color::clear_color = sge::image::colors::black())
	)
{
}

boost::statechart::result
sanguis::client::states::menu::react(
	tick_event const &t)
{
	context<machine>().dispatch();

	menu_.process(
		t.delta()
	);

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
		std::tr1::bind(
			&menu::handle_default_msg,
			this,
			std::tr1::placeholders::_1
		)
	);
}

boost::statechart::result
sanguis::client::states::menu::handle_default_msg(
	messages::base const &)
{
	return forward_event();
}

boost::statechart::result
sanguis::client::states::menu::operator()(
	messages::net_error const &e)
{
	menu_.connection_error(
		sge::utf8::convert(
			e.get<messages::roles::error_message>()
		)
	);
	return discard_event();
}

boost::statechart::result
sanguis::client::states::menu::operator()(
	messages::connect const &)
{
	context<machine>().send(
		messages::create(
			messages::client_info(
				sge::utf8::convert(
					SGE_TEXT("player1")
				)
			)
		)
	);
	return discard_event();
}

boost::statechart::result
sanguis::client::states::menu::operator()(
	messages::disconnect const &)
{
	menu_.connection_error(
		SGE_TEXT("The server closed the connection"));
	return discard_event();
}

boost::statechart::result
sanguis::client::states::menu::operator()(
	messages::assign_id const &m)
{
	SGE_LOG_DEBUG(
		log(),
		sge::log::_
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
	switch (
		static_cast<connect_state::type>(
			m.get<messages::roles::followup>()))
	{
		case connect_state::unpaused:
			SGE_LOG_DEBUG(
				log(),
				sge::log::_
					<< SGE_TEXT("switching to state \"unpaused\""));
			return transit<unpaused>();
		case connect_state::paused:
			SGE_LOG_DEBUG(
				log(),
				sge::log::_
					<< SGE_TEXT("switching to state \"paused\""));
			return transit<paused>();
	}
	throw sge::exception(
		SGE_TEXT("invalid followup state!"));
}

sge::log::object &
sanguis::client::states::menu::log()
{
	static sge::log::object log_(
		sge::log::parameters::inherited(
			client::log(),
			SGE_TEXT("states::menu: ")
		)
	);
	return log_;
}

void sanguis::client::states::menu::connect(
	sge::string const &host,
	sge::string const &port)
{
	try
	{
		context<machine>().connect(
			sge::iconv(
				host
			),
			sge::lexical_cast<
				net::port_type
			>(
				port
			)
		);
	}
	catch (sge::bad_lexical_cast const &)
	{
		menu_.connection_error(
			SGE_TEXT("invalid port specification")
		);
	}
}

void sanguis::client::states::menu::start_server()
{
	context<machine>().start_server();
}

void sanguis::client::states::menu::cancel_connect()
{
	context<machine>().cancel_connect();
}
