#include <sanguis/log_parameters.hpp>
#include <sanguis/client/machine.hpp>
#include <sanguis/client/events/action.hpp>
#include <sanguis/client/events/connected.hpp>
#include <sanguis/client/events/menu.hpp>
#include <sanguis/client/events/message.hpp>
#include <sanguis/client/events/net_error.hpp>
#include <sanguis/client/events/render.hpp>
#include <sanguis/client/events/tick.hpp>
#include <sanguis/client/states/log_location.hpp>
#include <sanguis/client/states/menu.hpp>
#include <sanguis/client/states/waiting_for_player.hpp>
#include <sanguis/messages/base.hpp>
#include <sanguis/messages/connect_state.hpp>
#include <sanguis/messages/create.hpp>
#include <sanguis/messages/client_info.hpp>
#include <sanguis/messages/call/object.hpp>
#include <sge/charconv/fcppt_string_to_utf8.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/output.hpp>
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
		>().renderer(),
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
		)
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

	return
		this->discard_event();
}

boost::statechart::result
sanguis::client::states::menu::react(
	sanguis::client::events::message const &_message
)
{
	static sanguis::messages::call::object<
		boost::mpl::vector1<
			sanguis::messages::connect_state
		>,
		menu
	> dispatcher;

	return
		dispatcher(
			*_message.value(),
			*this,
			std::bind(
				&sanguis::client::states::menu::handle_default_msg,
				this,
				std::placeholders::_1
			)
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
			<< FCPPT_TEXT("menu: connect")
	);

	this->context<
		sanguis::client::machine
	>().send(
		*sanguis::messages::create(
			sanguis::messages::client_info(
				sge::charconv::fcppt_string_to_utf8(
					FCPPT_TEXT("player1") // TODO!
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

boost::statechart::result
sanguis::client::states::menu::operator()(
	sanguis::messages::connect_state const &_state // TODO: do we need this?
)
{
	FCPPT_LOG_DEBUG(
		::logger,
		fcppt::log::_
			<< FCPPT_TEXT("Received connect_state")
	);

	return
		this->transit<
			sanguis::client::states::waiting_for_player
		>();
}

boost::statechart::result
sanguis::client::states::menu::handle_default_msg(
	sanguis::messages::base const &
)
{
	return
		this->forward_event();
}
