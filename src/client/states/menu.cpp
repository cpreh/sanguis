#include "menu.hpp"
#include "waiting_for_player.hpp"
#include "../../messages/base.hpp"
#include "../../messages/create.hpp"
#include "../../messages/client_info.hpp"
#include "../../messages/call/object.hpp"
#include "../../exception.hpp"
#include "../../cast_enum.hpp"
#include "../machine.hpp"
#include "../events/action.hpp"
#include "../events/connected.hpp"
#include "../events/menu.hpp"
#include "../events/message.hpp"
#include "../events/net_error.hpp"
#include "../events/tick.hpp"
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
#include <fcppt/from_std_string.hpp>
#include <fcppt/lexical_cast.hpp>
#include <fcppt/text.hpp>
#include <fcppt/to_std_string.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <ostream>

sanguis::client::states::menu::menu(
	my_context _ctx
)
:
	my_base(
		_ctx
	),
	menu_(
		context<machine>().settings(),
		context<machine>().gui(),
		gui::menu::callbacks::object(
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
				&machine::quickstart,
				&context<machine>(),
				std::tr1::placeholders::_1
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

sanguis::client::states::menu::~menu()
{
}

boost::statechart::result
sanguis::client::states::menu::react(
	events::tick const &_event
)
{
	menu_.process(
		_event.delta()
	);

	return discard_event();
}

boost::statechart::result
sanguis::client::states::menu::react(
	events::message const &_message
)
{
	static messages::call::object<
		boost::mpl::vector1<
			messages::connect_state
		>,
		menu
	> dispatcher;

	return
		dispatcher(
			*_message.value(),
			*this,
			std::tr1::bind(
				&menu::handle_default_msg,
				this,
				std::tr1::placeholders::_1
			)
		);
}

boost::statechart::result
sanguis::client::states::menu::react(
	events::connected const &
)
{
	FCPPT_LOG_DEBUG(
		menu::log(),
		fcppt::log::_
			<< FCPPT_TEXT("menu: connect")
	);
		
	context<machine>().send(
		messages::create(
			messages::client_info(
				fcppt::utf8::convert(
					FCPPT_TEXT("player1") // TODO!
				)
			)
		)
	);

	return discard_event();
}

boost::statechart::result
sanguis::client::states::menu::react(
	events::net_error const &_error
)
{
	menu_.connection_error(
		fcppt::from_std_string(
			_error.code().message()
		)
	);

	return discard_event();
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
	messages::connect_state const &_state // TODO: do we need this?
)
{
	FCPPT_LOG_DEBUG(
		menu::log(),
		fcppt::log::_
			<< FCPPT_TEXT("Received connect_state")
	);

	return transit<waiting_for_player>();
}

fcppt::log::object &
sanguis::client::states::menu::log()
{
	static fcppt::log::object my_logger(
		fcppt::log::parameters::inherited(
			client::log(),
			FCPPT_TEXT("states::menu")
		)
	);

	return my_logger;
}

void
sanguis::client::states::menu::connect(
	fcppt::string const &_host,
	fcppt::string const &_port
)
{
	try
	{
		context<machine>().connect(
			fcppt::to_std_string(
				_host
			),
			fcppt::lexical_cast<
				net::port
			>(
				_port
			)
		);
	}
	catch(
		fcppt::bad_lexical_cast const &
	)
	{
		menu_.connection_error(
			FCPPT_TEXT("invalid port specification")
		);
	}
}

void
sanguis::client::states::menu::cancel_connect()
{
	context<machine>().cancel_connect();
}
