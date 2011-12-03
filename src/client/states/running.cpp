#include <sanguis/client/states/running.hpp>
#include <sanguis/client/states/menu.hpp>
#include <sanguis/client/daytime_settings.hpp>
#include <sanguis/client/log.hpp>
#include <sanguis/client/make_send_callback.hpp>
#include <sanguis/client/music_handler.hpp>
#include <sanguis/client/console/object.hpp>
#include <sanguis/client/draw2d/scene/object.hpp>
#include <sanguis/client/events/connected.hpp>
#include <sanguis/client/events/menu.hpp>
#include <sanguis/client/events/message.hpp>
#include <sanguis/client/events/net_error.hpp>
#include <sanguis/client/events/overlay.hpp>
#include <sanguis/client/events/render.hpp>
#include <sanguis/client/events/tick.hpp>
#include <sanguis/messages/call/object.hpp>
#include <sanguis/messages/create.hpp>
#include <sanguis/load/context.hpp>
#include <sge/audio/player.hpp>
#include <sge/console/object.hpp>
#include <sge/font/text/from_fcppt_string.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/state/bool.hpp>
#include <sge/renderer/state/list.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/utf8/to_fcppt_string.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/mpl/vector/vector10.hpp>
#include <fcppt/config/external_end.hpp>

sanguis::client::states::running::running(
	my_context _ctx
)
:
	my_base(
		_ctx
	),
	renderer_state_(
		context<machine>().renderer(),
		sge::renderer::state::list
			(sge::renderer::state::bool_::clear_back_buffer = false)
			(sge::renderer::state::bool_::clear_depth_buffer = false)
	),
	console_(
		fcppt::make_unique_ptr<
			client::console::object
		>(
			fcppt::ref(
				context<machine>().console_gfx()
			),
			client::make_send_callback(
				context<machine>()
			)
		)
	),
	daytime_settings_(
		fcppt::make_unique_ptr<
			client::daytime_settings
		>(
			fcppt::ref(
				console_->sge_console()
			)
		)
	),
	drawer_(
		fcppt::make_unique_ptr<
			draw2d::scene::object
		>(
			fcppt::cref(
				context<machine>().resources()
			),
			fcppt::ref(
				context<machine>().renderer()
			),
			fcppt::ref(
				context<machine>().font_metrics()
			),
			fcppt::ref(
				context<machine>().font_drawer()
			),
			fcppt::ref(
				context<machine>().audio_player().listener()
			),
			daytime_settings_->current_time(),
			fcppt::ref(
				context<machine>().viewport_manager()
			)
		)
	),
	music_(
		fcppt::make_unique_ptr<
			client::music_handler
		>(
			fcppt::ref(
				console_->sge_console()
			),
			fcppt::cref(
				context<machine>().resources().resources().sounds()
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
	events::tick const &_event
)
{
	drawer_->set_time(
		daytime_settings_->current_time()
	);

	drawer_->update(
		_event.delta()
	);

	music_->process();

	return this->discard_event();
}

boost::statechart::result
sanguis::client::states::running::react(
	events::render const &
)
{
	drawer_->draw();

	this->post_event(
		events::overlay()
	);

	return this->discard_event();
}

boost::statechart::result
sanguis::client::states::running::react(
	events::message const &_event
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
			std::tr1::bind(
				&running::handle_default_msg,
				this,
				std::tr1::placeholders::_1
			)
		);
}

boost::statechart::result
sanguis::client::states::running::react(
	events::net_error const &_error
)
{
	return transit<menu>();
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
		sge::font::text::from_fcppt_string(
			fcppt::utf8::to_fcppt_string(
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
			fcppt::utf8::to_fcppt_string(
				_message.get<
					sanguis::messages::roles::command_name
				>()
			)
		),
		description(
			fcppt::utf8::to_fcppt_string(
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

	return discard_event();
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

	return discard_event();
}

sanguis::client::control::environment &
sanguis::client::states::running::control_environment()
{
	return drawer_->control_environment();
}

sanguis::client::console::object &
sanguis::client::states::running::console()
{
	return *console_;
}

boost::statechart::result
sanguis::client::states::running::handle_default_msg(
	sanguis::messages::base const &_message
)
{
	drawer_->process_message(
		_message
	);

	return discard_event();
}
