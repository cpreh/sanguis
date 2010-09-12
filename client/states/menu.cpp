#include "menu.hpp"
#include "paused.hpp"
#include "unpaused.hpp"
#include "../../messages/base.hpp"
#include "../../messages/create.hpp"
#include "../../messages/client_info.hpp"
#include "../../messages/call/object.hpp"
#include "../../exception.hpp"
#include "../../cast_enum.hpp"
#include "../machine.hpp"
#include "../events/message.hpp"
#include "../events/tick.hpp"
#include "../events/menu.hpp"
#include "../log.hpp"
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <sge/image/colors.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/log/parameters/inherited.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/utf8/convert.hpp>
#include <fcppt/lexical_cast.hpp>
#include <fcppt/text.hpp>
#include <fcppt/to_std_string.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <ostream>

sanguis::client::states::menu::menu(
	my_context ctx
)
:
	my_base(ctx),
	menu_(
		context<machine>().settings(),
		context<machine>().renderer(),
		context<machine>().image_loader(),
		context<machine>().font_metrics(),
		context<machine>().input_system(),
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
	events::tick const &_event
)
{
	context<machine>().dispatch();

	menu_.process(
		_event.delta()
	);

	return discard_event();
}

boost::statechart::result
sanguis::client::states::menu::react(
	events::message const &m
)
{
	static messages::call::object<
		boost::mpl::vector4<
			messages::connect_state,
			messages::connect,
			messages::disconnect,
			messages::net_error
		>,
		menu
	> dispatcher;

	return dispatcher(
		*m.value(),
		*this,
		std::tr1::bind(
			&menu::handle_default_msg,
			this,
			std::tr1::placeholders::_1
		)
	);
}

boost::statechart::result
sanguis::client::states::menu::handle_default_msg(
	messages::base const &
)
{
	return forward_event();
}

boost::statechart::result
sanguis::client::states::menu::operator()(
	messages::net_error const &e
)
{
	menu_.connection_error(
		fcppt::utf8::convert(
			e.get<messages::roles::error_message>()
		)
	);

	return discard_event();
}

boost::statechart::result
sanguis::client::states::menu::operator()(
	messages::connect const &
)
{
	context<machine>().send(
		messages::create(
			messages::client_info(
				fcppt::utf8::convert(
					FCPPT_TEXT("player1")
				)
			)
		)
	);

	return discard_event();
}

boost::statechart::result
sanguis::client::states::menu::operator()(
	messages::disconnect const &
)
{
	menu_.connection_error(
		FCPPT_TEXT("The server closed the connection")
	);

	return discard_event();
}

boost::statechart::result
sanguis::client::states::menu::operator()(
	messages::connect_state const &m
)
{
	FCPPT_LOG_DEBUG(
		log(),
		fcppt::log::_
			<< FCPPT_TEXT("Received connect_state")
	);

	switch (
		SANGUIS_CAST_ENUM(
			connect_state,
			m.get<messages::roles::connect_state>()
		)
	)
	{
		case connect_state::unpaused:
			FCPPT_LOG_DEBUG(
				log(),
				fcppt::log::_
					<< FCPPT_TEXT("switching to state \"unpaused\"")
			);

			return transit<unpaused>();
		case connect_state::paused:
			FCPPT_LOG_DEBUG(
				log(),
				fcppt::log::_
					<< FCPPT_TEXT("switching to state \"paused\"")
			);

			return transit<paused>();
		case connect_state::size:
			break;
	}

	throw exception(
		FCPPT_TEXT("invalid connect_state!")
	);
}

fcppt::log::object &
sanguis::client::states::menu::log()
{
	static fcppt::log::object log_(
		fcppt::log::parameters::inherited(
			client::log(),
			FCPPT_TEXT("states::menu")
		)
	);

	return log_;
}

void
sanguis::client::states::menu::connect(
	fcppt::string const &host,
	fcppt::string const &port
)
{
	try
	{
		context<machine>().connect(
			fcppt::to_std_string(
				host
			),
			fcppt::lexical_cast<
				net::port_type
			>(
				port
			)
		);
	}
	catch (fcppt::bad_lexical_cast const &)
	{
		menu_.connection_error(
			FCPPT_TEXT("invalid port specification")
		);
	}
}

void
sanguis::client::states::menu::start_server()
{
	context<machine>().start_server();
}

void
sanguis::client::states::menu::cancel_connect()
{
	context<machine>().cancel_connect();
}
