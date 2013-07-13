#include <sanguis/client/daytime_settings.hpp>
#include <sanguis/client/log.hpp>
#include <sanguis/client/machine.hpp>
#include <sanguis/client/make_send_callback.hpp>
#include <sanguis/client/console/object.hpp>
#include <sanguis/client/control/environment_fwd.hpp>
#include <sanguis/client/control/input_translator.hpp>
#include <sanguis/client/control/actions/any_fwd.hpp>
#include <sanguis/client/draw2d/scene/object.hpp>
#include <sanguis/client/events/action.hpp>
#include <sanguis/client/events/connected.hpp>
#include <sanguis/client/events/menu.hpp>
#include <sanguis/client/events/message.hpp>
#include <sanguis/client/events/net_error.hpp>
#include <sanguis/client/events/overlay.hpp>
#include <sanguis/client/events/render.hpp>
#include <sanguis/client/events/tick.hpp>
#include <sanguis/client/states/menu.hpp>
#include <sanguis/client/states/running.hpp>
#include <sanguis/messages/add_console_command.hpp>
#include <sanguis/messages/base_fwd.hpp>
#include <sanguis/messages/console_print.hpp>
#include <sanguis/messages/create.hpp>
#include <sanguis/messages/level_up.hpp>
#include <sanguis/messages/pause.hpp>
#include <sanguis/messages/unpause.hpp>
#include <sanguis/messages/call/object.hpp>
#include <sanguis/load/context.hpp>
#include <sge/charconv/utf8_string_to_fcppt.hpp>
#include <sge/console/object.hpp>
#include <sge/font/from_fcppt_string.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <boost/statechart/result.hpp>
#include <functional>
#include <fcppt/config/external_end.hpp>


sanguis::client::states::running::running(
	my_context _ctx
)
:
	my_base(
		_ctx
	),
	console_(
		fcppt::make_unique_ptr<
			sanguis::client::console::object
		>(
			this->context<
				sanguis::client::machine
			>().console_gfx(),
			sanguis::client::make_send_callback(
				this->context<
					sanguis::client::machine
				>()
			)
		)
	),
	daytime_settings_(
		fcppt::make_unique_ptr<
			sanguis::client::daytime_settings
		>(
			console_->sge_console()
		)
	),
	drawer_(
		fcppt::make_unique_ptr<
			sanguis::client::draw2d::scene::object
		>(
			this->context<
				sanguis::client::machine
			>().resources(),
			this->context<
				sanguis::client::machine
			>().renderer(),
			this->context<
				sanguis::client::machine
			>().font_object(),
			daytime_settings_->current_time(),
			this->context<
				sanguis::client::machine
			>().viewport_manager()
		)
	),
	input_translator_(
		fcppt::make_unique_ptr<
			sanguis::client::control::input_translator
		>(
			this->context<
				sanguis::client::machine
			>().keyboard(),
			this->context<
				sanguis::client::machine
			>().cursor(),
			std::bind(
				&sanguis::client::states::running::handle_player_action,
				this,
				std::placeholders::_1
			)
		)
	)
{
}

sanguis::client::states::running::~running()
{
}

boost::statechart::result
sanguis::client::states::running::react(
	sanguis::client::events::tick const &_event
)
{
	drawer_->set_time(
		daytime_settings_->current_time()
	);

	drawer_->update(
		_event.delta()
	);

	return
		this->discard_event();
}

boost::statechart::result
sanguis::client::states::running::react(
	sanguis::client::events::render const &_event
)
{
	drawer_->draw(
		_event.context()
	);

	this->post_event(
		sanguis::client::events::overlay(
			_event.context()
		)
	);

	return
		this->discard_event();
}

boost::statechart::result
sanguis::client::states::running::react(
	sanguis::client::events::message const &_event
)
{
	static sanguis::messages::call::object<
		boost::mpl::vector5<
			sanguis::messages::level_up,
			sanguis::messages::console_print,
			sanguis::messages::add_console_command,
			sanguis::messages::pause,
			sanguis::messages::unpause
		>,
		running
	> dispatcher;

	return
		dispatcher(
			*_event.value(),
			*this,
			std::bind(
				&sanguis::client::states::running::handle_default_msg,
				this,
				std::placeholders::_1
			)
		);
}

boost::statechart::result
sanguis::client::states::running::react(
	sanguis::client::events::net_error const &_error
)
{
	return
		this->transit<
			sanguis::client::states::menu
		>();
}

boost::statechart::result
sanguis::client::states::running::operator()(
	sanguis::messages::level_up const &_message
)
{
	drawer_->process_message(
		*sanguis::messages::create(
			_message
		)
	);

	return discard_event();
}

boost::statechart::result
sanguis::client::states::running::operator()(
	sanguis::messages::console_print const &_message
)
{
	console_->sge_console().emit_message(
		sge::font::from_fcppt_string(
			sge::charconv::utf8_string_to_fcppt(
				_message.get<
					sanguis::messages::string
				>()
			)
		)
	);

	return discard_event();
}

boost::statechart::result
sanguis::client::states::running::operator()(
	sanguis::messages::add_console_command const &_message
)
{
	fcppt::string const
		name(
			sge::charconv::utf8_string_to_fcppt(
				_message.get<
					sanguis::messages::roles::command_name
				>()
			)
		),
		description(
			sge::charconv::utf8_string_to_fcppt(
				_message.get<
					sanguis::messages::roles::command_description
				>()
			)
		);

	FCPPT_LOG_DEBUG(
		sanguis::client::log(),
		fcppt::log::_
			<< FCPPT_TEXT("Got a new console command: \"")
			<< name
			<< FCPPT_TEXT("\", description: \"")
			<< description
			<< FCPPT_TEXT('"')
	);

	console_->register_server_command(
		name,
		description
	);

	return
		this->discard_event();
}

boost::statechart::result
sanguis::client::states::running::operator()(
	sanguis::messages::pause const &
)
{
	drawer_->pause(
		true
	);

	return discard_event();
}

boost::statechart::result
sanguis::client::states::running::operator()(
	sanguis::messages::unpause const &
)
{
	drawer_->pause(
		false
	);

	return
		this->discard_event();
}

sanguis::client::control::environment &
sanguis::client::states::running::control_environment()
{
	return
		drawer_->control_environment();
}

sanguis::client::console::object &
sanguis::client::states::running::console()
{
	return
		*console_;
}

void
sanguis::client::states::running::handle_player_action(
	sanguis::client::control::actions::any const &_action
)
{
	this->post_event(
		sanguis::client::events::action(
			_action
		)
	);
}

boost::statechart::result
sanguis::client::states::running::handle_default_msg(
	sanguis::messages::base const &_message
)
{
	drawer_->process_message(
		_message
	);

	return
		this->discard_event();
}
