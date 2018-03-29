#include <sanguis/duration.hpp>
#include <sanguis/io_service.hpp>
#include <sanguis/log_parameters.hpp>
#include <sanguis/client/cursor_fwd.hpp>
#include <sanguis/client/log_location.hpp>
#include <sanguis/client/machine.hpp>
#include <sanguis/client/args/result_fwd.hpp>
#include <sanguis/client/config/settings/object_fwd.hpp>
#include <sanguis/client/events/connected.hpp>
#include <sanguis/client/events/input.hpp>
#include <sanguis/client/events/message.hpp>
#include <sanguis/client/events/net_error.hpp>
#include <sanguis/client/events/render.hpp>
#include <sanguis/client/events/tick.hpp>
#include <sanguis/client/load/context_fwd.hpp>
#include <sanguis/client/net/deserialize.hpp>
#include <sanguis/client/net/serialize_to_circular_buffer.hpp>
#include <sanguis/messages/client/base.hpp>
#include <sanguis/messages/server/base.hpp>
#include <sanguis/messages/server/unique_ptr.hpp>
#include <sanguis/net/receive_buffer_size.hpp>
#include <sanguis/net/send_buffer_size.hpp>
#include <alda/net/host.hpp>
#include <alda/net/parameters.hpp>
#include <alda/net/port.hpp>
#include <alda/net/buffer/circular_receive/streambuf_fwd.hpp>
#include <alda/net/client/connect_callback.hpp>
#include <alda/net/client/data_callback.hpp>
#include <alda/net/client/error_callback.hpp>
#include <sge/console/gfx/object.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/gui/style/base_fwd.hpp>
#include <sge/input/event_base.hpp>
#include <sge/renderer/context/scoped_ffp.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/renderer/event/render.hpp>
#include <sge/renderer/target/onscreen.hpp>
#include <sge/systems/instance.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <sge/window/system.hpp>
#include <awl/event/base.hpp>
#include <awl/event/base_unique_ptr.hpp>
#include <awl/event/container.hpp>
#include <awl/main/exit_code.hpp>
#include <awl/main/exit_success.hpp>
#include <fcppt/const.hpp>
#include <fcppt/from_std_string.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/cast/dynamic_fun.hpp>
#include <fcppt/either/match.hpp>
#include <fcppt/log/_.hpp>
#include <fcppt/log/context_fwd.hpp>
#include <fcppt/log/debug.hpp>
#include <fcppt/log/error.hpp>
#include <fcppt/log/name.hpp>
#include <fcppt/optional/maybe.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/variant/dynamic_cast.hpp>
#include <fcppt/variant/match.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/system/error_code.hpp>
#include <boost/system/system_error.hpp>
#include <brigand/sequences/list.hpp>
#include <functional>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::client::machine::machine(
	fcppt::log::context &_log_context,
	sanguis::client::config::settings::object &_settings,
	sanguis::client::args::result const &_options,
	sanguis::client::server_callback const &_server_callback,
	sanguis::client::load::context const &_resources,
	sge::gui::style::base const &_gui_style,
	sge::window::system &_window_system,
	sge::font::object &_font_object,
	sge::console::gfx::object &_console_gfx,
	sge::renderer::device::ffp &_renderer,
	sanguis::io_service &_io_service,
	sge::viewport::manager &_viewport_manager,
	sanguis::client::cursor &_cursor_gfx
)
:
	log_context_{
		_log_context
	},
	log_{
		_log_context,
		sanguis::client::log_location(),
		sanguis::log_parameters(
			fcppt::log::name{
				FCPPT_TEXT("machine")
			}
		)
	},
	settings_(
		_settings
	),
	options_(
		_options
	),
	resources_(
		_resources
	),
	gui_style_(
		_gui_style
	),
	renderer_(
		_renderer
	),
	viewport_manager_(
		_viewport_manager
	),
	net_(
		alda::net::parameters(
			_log_context,
			_io_service.impl(),
			sanguis::net::send_buffer_size(),
			sanguis::net::receive_buffer_size()
		)
	),
	s_conn_(
		net_.register_connect(
			alda::net::client::connect_callback{
				std::bind(
					&sanguis::client::machine::connect_callback,
					this
				)
			}
		)
	),
	s_disconn_(
		net_.register_error(
			alda::net::client::error_callback{
				std::bind(
					&sanguis::client::machine::error_callback,
					this,
					std::placeholders::_1,
					std::placeholders::_2
				)
			}
		)
	),
	s_data_(
		net_.register_data(
			alda::net::client::data_callback{
				std::bind(
					&sanguis::client::machine::data_callback,
					this,
					std::placeholders::_1
				)
			}
		)
	),
	window_system_(
		_window_system
	),
	font_object_(
		_font_object
	),
	console_gfx_(
		_console_gfx
	),
	server_callback_(
		_server_callback
	),
	cursor_gfx_(
		_cursor_gfx
	)
{
}

sanguis::client::machine::~machine()
{
}

void
sanguis::client::machine::quickstart(
	alda::net::port const _port
)
{
	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::_
			<< FCPPT_TEXT("quickstart()")
	);

	try
	{
		server_callback_(
			_port
		);
	}
	catch(
		boost::system::system_error const &_error
	)
	{
		this->error_callback(
			fcppt::from_std_string(
				_error.what()
			),
			_error.code()
		);

		return;
	}

	this->connect(
		alda::net::host(
			"localhost"
		),
		_port
	);
}

void
sanguis::client::machine::connect(
	alda::net::host const &_host,
	alda::net::port const _port
)
{
	net_.connect(
		_host,
		_port
	);
}

void
sanguis::client::machine::disconnect()
{
	net_.disconnect();
}

void
sanguis::client::machine::send(
	sanguis::messages::client::base const &_message
)
{
	if(
		!sanguis::client::net::serialize_to_circular_buffer(
			_message,
			net_.send_buffer()
		)
	)
	{
		FCPPT_LOG_ERROR(
			log_,
			fcppt::log::_
				<< FCPPT_TEXT("Not enough space left in the send_buffer")
		);
		// FIXME: We have to wait for free space here!
		// Any client message except the very first message (which is part of the handshake)
		// can technically be lost, so leave this for now.
	}

	net_.queue_send();
}

bool
sanguis::client::machine::process(
	sanguis::duration const &_time
)
{
	this->process_event(
		sanguis::client::events::tick(
			_time
		)
	);

	return
		fcppt::either::match(
			window_system_.poll(),
			[](
				// TODO: Return this from client::object
				awl::main::exit_code const _result
			)
			{
				return
					false;
			},
			[
				this
			](
				awl::event::container const &_events
			)
			{
				for(
					awl::event::base_unique_ptr const &event
					:
					_events
				)
					this->process_sge_event(
						*event
					);

				return
					true;
			}
		);
}

void
sanguis::client::machine::quit()
{
	FCPPT_LOG_DEBUG(
		log_,
		fcppt::log::_
			<< FCPPT_TEXT("Exiting the client!")
	);

	window_system_.quit(
		awl::main::exit_success()
	);
}

sanguis::client::config::settings::object &
sanguis::client::machine::settings()
{
	return
		settings_;
}

sanguis::client::args::result const &
sanguis::client::machine::options() const
{
	return
		options_;
}

sge::gui::style::base const &
sanguis::client::machine::gui_style() const
{
	return
		gui_style_;
}

sge::renderer::device::ffp &
sanguis::client::machine::renderer() const
{
	return
		renderer_;
}

sge::font::object &
sanguis::client::machine::font_object() const
{
	return
		font_object_;
}

sge::console::gfx::object &
sanguis::client::machine::console_gfx()
{
	return
		console_gfx_;
}

sanguis::client::load::context const &
sanguis::client::machine::resources() const
{
	return
		resources_;
}

sge::viewport::manager &
sanguis::client::machine::viewport_manager() const
{
	return
		viewport_manager_;
}

sanguis::client::cursor &
sanguis::client::machine::cursor_gfx() const
{
	return
		cursor_gfx_;
}

fcppt::log::context &
sanguis::client::machine::log_context() const
{
	return
		log_context_;
}

void
sanguis::client::machine::draw()
{
	sge::renderer::context::scoped_ffp const block(
		renderer_,
		renderer_.onscreen_target()
	);

	this->process_event(
		sanguis::client::events::render(
			block.get()
		)
	);
}

void
sanguis::client::machine::process_sge_event(
	awl::event::base const &_event
)
{
	fcppt::optional::maybe_void(
		fcppt::variant::dynamic_cast_<
			brigand::list<
				sge::renderer::event::render const,
				sge::input::event_base const
			>,
			fcppt::cast::dynamic_fun
		>(
			_event
		),
		[
			this
		](
			auto const &_variant
		)
		{
			fcppt::variant::match(
				_variant,
				[
					this
				](
					fcppt::reference<
						sge::renderer::event::render const
					>
				)
				{
					this->draw();
				},
				[
					this
				](
					fcppt::reference<
						sge::input::event_base const
					> const _input_event
				)
				{
					this->process_event(
						sanguis::client::events::input(
							_input_event.get()
						)
					);
				}
			);
		}
	);
}

void
sanguis::client::machine::connect_callback()
{
	this->process_event(
		sanguis::client::events::connected()
	);
}

void
sanguis::client::machine::error_callback(
	fcppt::string const &_message,
	boost::system::error_code const &_error
)
{
	this->process_event(
		sanguis::client::events::net_error(
			_message,
			_error
		)
	);
}

void
sanguis::client::machine::data_callback(
	alda::net::buffer::circular_receive::streambuf &_data
)
{
	while(
		fcppt::optional::maybe(
			sanguis::client::net::deserialize(
				_data
			),
			fcppt::const_(
				false
			),
			[
				this
			](
				sanguis::messages::server::unique_ptr &&_message
			)
			{
				this->process_event(
					sanguis::client::events::message(
						std::move(
							_message
						)
					)
				);

				return
					true;
			}
		)
	)
		;
}
