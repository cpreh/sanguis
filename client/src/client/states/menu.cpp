#include <sanguis/log_parameters.hpp>
#include <sanguis/client/cursor.hpp>
#include <sanguis/client/dispatch.hpp>
#include <sanguis/client/machine.hpp>
#include <sanguis/client/events/action.hpp>
#include <sanguis/client/events/connected.hpp>
#include <sanguis/client/events/menu.hpp>
#include <sanguis/client/events/message.hpp>
#include <sanguis/client/events/net_error.hpp>
#include <sanguis/client/events/render.hpp>
#include <sanguis/client/events/tick.hpp>
#include <sanguis/client/load/context.hpp>
#include <sanguis/client/load/resource/context.hpp>
#include <sanguis/client/states/log_location.hpp>
#include <sanguis/client/states/menu.hpp>
#include <sanguis/client/states/waiting_for_player.hpp>
#include <sanguis/messages/call/result.hpp>
#include <sanguis/messages/client/create.hpp>
#include <sanguis/messages/client/info.hpp>
#include <sanguis/messages/roles/player_name.hpp>
#include <sanguis/messages/server/base.hpp>
#include <sanguis/messages/server/connected.hpp>
#include <sge/charconv/fcppt_string_to_utf8.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/parameters/object.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/statechart/result.hpp>
#include <ostream>
#include <functional>
#include <fcppt/config/external_end.hpp>


namespace
{

fcppt::log::object logger(
	sanguis::log_parameters(
		sanguis::client::states::log_location()
		/
		FCPPT_TEXT("menu")
	)
);

}

sanguis::client::states::menu::menu(
	my_context _ctx
)
:
	my_base(
		_ctx
	),
	menu_(
		this->context<
			sanguis::client::machine
		>().renderer_system(),
		this->context<
			sanguis::client::machine
		>().renderer(),
		this->context<
			sanguis::client::machine
		>().renderer_index(),
		this->context<
			sanguis::client::machine
		>().viewport_manager(),
		this->context<
			sanguis::client::machine
		>().font_object(),
		this->context<
			sanguis::client::machine
		>().cursor(),
		this->context<
			sanguis::client::machine
		>().keyboard(),
		this->context<
			sanguis::client::machine
		>().resources().resources().textures(),
		this->context<
			sanguis::client::machine
		>().settings(),
		sanguis::client::gui::menu::callbacks::object(
			std::bind(
				&sanguis::client::machine::connect,
				&this->context<
					sanguis::client::machine
				>(),
				std::placeholders::_1,
				std::placeholders::_2
			),
			std::bind(
				&sanguis::client::machine::disconnect,
				&this->context<
					sanguis::client::machine
				>()
			),
			std::bind(
				&sanguis::client::machine::quickstart,
				&this->context<
					sanguis::client::machine
				>(),
				std::placeholders::_1
			),
			std::bind(
				&sanguis::client::machine::quit,
				&this->context<
					sanguis::client::machine
				>()
			)
		),
		this->context<
			sanguis::client::machine
		>().gui_style()
	)
{
}

sanguis::client::states::menu::~menu()
{
}

boost::statechart::result
sanguis::client::states::menu::react(
	sanguis::client::events::tick const &_event
)
{
	menu_.process(
		_event.delta()
	);

	return
		this->discard_event();
}

boost::statechart::result
sanguis::client::states::menu::react(
	sanguis::client::events::render const &_event
)
{
	menu_.draw(
		_event.context()
	);

	this->context<
		sanguis::client::machine
	>().cursor_gfx().draw(
		_event.context()
	);

	return
		this->discard_event();
}

boost::statechart::result
sanguis::client::states::menu::react(
	sanguis::client::events::message const &_message
)
{
	auto const handle_default_msg(
		[
			this
		](
			sanguis::messages::server::base const &
		)
		{
			return
				this->forward_event();
		}
	);

	return
		sanguis::client::dispatch<
			boost::mpl::vector1<
				sanguis::messages::server::connected
			>
		>(
			*this,
			_message,
			handle_default_msg
		);
}

boost::statechart::result
sanguis::client::states::menu::react(
	sanguis::client::events::connected const &
)
{
	FCPPT_LOG_DEBUG(
		::logger,
		fcppt::log::_
			<< FCPPT_TEXT("Connected, sending client info")
	);

	this->context<
		sanguis::client::machine
	>().send(
		sanguis::messages::client::create(
			sanguis::messages::client::info(
				sanguis::messages::roles::player_name{} =
					sge::charconv::fcppt_string_to_utf8(
						menu_.player_name()
					)
			)
		)
	);

	return
		this->discard_event();
}

boost::statechart::result
sanguis::client::states::menu::react(
	sanguis::client::events::net_error const &_error
)
{
	menu_.connection_error(
		fcppt::from_std_string(
			_error.code().message()
		)
	);

	return
		this->discard_event();
}

sanguis::messages::call::result
sanguis::client::states::menu::operator()(
	sanguis::messages::server::connected const &
)
{
	FCPPT_LOG_DEBUG(
		::logger,
		fcppt::log::_
			<< FCPPT_TEXT("Received connected message")
	);

	return
		sanguis::messages::call::result(
			this->transit<
				sanguis::client::states::waiting_for_player
			>()
		);
}
