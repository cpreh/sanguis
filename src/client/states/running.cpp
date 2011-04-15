#include "running.hpp"
#include "menu.hpp"
#include "../daytime_settings.hpp"
#include "../log.hpp"
#include "../music_handler.hpp"
#include "../console/object.hpp"
#include "../events/connected.hpp"
#include "../events/menu.hpp"
#include "../events/message.hpp"
#include "../events/net_error.hpp"
#include "../events/overlay.hpp"
#include "../events/render.hpp"
#include "../events/tick.hpp"
#include "../draw2d/scene/object.hpp"
#include "../../messages/call/object.hpp"
#include "../../messages/create.hpp"
#include "../../load/context.hpp"
#include <sge/audio/player.hpp>
#include <sge/console/object.hpp>
#include <sge/font/text/from_fcppt_string.hpp>
#include <sge/renderer/device.hpp>
#include <sge/renderer/state/list.hpp>
#include <sge/renderer/state/var.hpp>
#include <sge/renderer/state/trampoline.hpp>
#include <fcppt/container/raw_vector_impl.hpp>
#include <fcppt/log/output.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/utf8/convert.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <boost/mpl/vector/vector10.hpp>

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
			(sge::renderer::state::bool_::clear_backbuffer = false)
			(sge::renderer::state::bool_::clear_zbuffer = false)
	),
	console_(
		fcppt::make_unique_ptr<
			client::console::object
		>(
			fcppt::ref(
				context<machine>().console_gfx()
			),
			std::tr1::bind(
				&machine::send,
				&context<machine>(),
				std::tr1::placeholders::_1
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
			context<machine>().resources(),
			context<machine>().renderer(),
			context<machine>().font_metrics(),
			fcppt::ref(
				context<machine>().font_drawer()
			),
			fcppt::ref(
				context<machine>().audio_player()->listener()
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
			context<machine>().resources().resources().sounds()
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
	context<machine>().resources().update(
		_event.delta()
	);

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
			fcppt::utf8::convert(
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
			fcppt::utf8::convert(
				_message.get<
					sanguis::messages::roles::command_name
				>()
			)
		),
		description(
			fcppt::utf8::convert(
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
