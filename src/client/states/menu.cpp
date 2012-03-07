#include <sanguis/client/states/menu.hpp>
#include <sanguis/client/states/waiting_for_player.hpp>
#include <sanguis/client/states/log_location.hpp>
#include <sanguis/client/machine.hpp>
#include <sanguis/client/events/action.hpp>
#include <sanguis/client/events/connected.hpp>
#include <sanguis/client/events/menu.hpp>
#include <sanguis/client/events/message.hpp>
#include <sanguis/client/events/net_error.hpp>
#include <sanguis/client/events/render.hpp>
#include <sanguis/client/events/tick.hpp>
#include <sanguis/messages/base.hpp>
#include <sanguis/messages/create.hpp>
#include <sanguis/messages/client_info.hpp>
#include <sanguis/messages/call/object.hpp>
#include <sanguis/cast_enum.hpp>
#include <sanguis/exception.hpp>
#include <sanguis/log_parameters.hpp>
#include <sge/charconv/fcppt_string_to_utf8.hpp>
#include <sge/renderer/state/bool.hpp>
#include <sge/renderer/state/list.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/log/parameters/object.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <ostream>
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
		context<machine>().settings(),
		context<machine>().gui(),
		gui::menu::callbacks::object(
			std::tr1::bind(
				&machine::connect,
				&context<machine>(),
				std::tr1::placeholders::_1,
				std::tr1::placeholders::_2
			),
			std::tr1::bind(
				&machine::disconnect,
				&context<machine>()
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
			(sge::renderer::state::bool_::clear_back_buffer = false)
			(sge::renderer::state::bool_::clear_depth_buffer = false)
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
	events::render const &
)
{
	menu_.draw();

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
		::logger,
		fcppt::log::_
			<< FCPPT_TEXT("menu: connect")
	);

	context<machine>().send(
		messages::create(
			messages::client_info(
				sge::charconv::fcppt_string_to_utf8(
					context<machine>().charconv_system(),
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
		::logger,
		fcppt::log::_
			<< FCPPT_TEXT("Received connect_state")
	);

	return transit<waiting_for_player>();
}
