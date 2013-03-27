#include <sanguis/log_parameters.hpp>
#include <sanguis/media_path.hpp>
#include <sanguis/client/log_location.hpp>
#include <sanguis/client/config/settings/object.hpp>
#include <sanguis/client/gui/menu/object.hpp>
#include <sanguis/client/gui/menu/connection_box.hpp>
#include <sanguis/client/gui/object.hpp>
#include <sge/cegui/from_cegui_string.hpp>
#include <sge/cegui/to_cegui_string.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/parse/ini/entry_name.hpp>
#include <sge/parse/ini/get_or_create.hpp>
#include <sge/parse/ini/section_name.hpp>
#include <sge/parse/ini/set_or_create.hpp>
#include <sge/parse/ini/string.hpp>
#include <sge/parse/ini/value.hpp>
#include <sge/renderer/clear/parameters.hpp>
#include <sge/renderer/context/ffp.hpp>
#include <alda/net/host.hpp>
#include <alda/net/port.hpp>
#include <fcppt/log/parameters/object.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/extract_from_string.hpp>
#include <fcppt/extract_from_string_exn.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/to_std_string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/Window.h>
#include <CEGUI/widgets/PushButton.h>
#include <functional>
#include <fcppt/config/external_end.hpp>

namespace
{

fcppt::log::object logger(
	sanguis::log_parameters(
		sanguis::client::log_location()
		/
		FCPPT_TEXT("menu")
		/
		FCPPT_TEXT("object")
	)
);

sge::parse::ini::section_name const
config_section(
	FCPPT_TEXT("gui_menu")
);

sge::parse::ini::entry_name const
	config_hostname_key(
		FCPPT_TEXT("hostname")
	),
	config_port_key(
		FCPPT_TEXT("port")
	),
	config_quickstart_port_key(
		FCPPT_TEXT("quickstartport")
	);
}

sanguis::client::gui::menu::object::object(
	config::settings::object &_settings,
	client::gui::object &_gui,
	callbacks::object const &_callbacks
)
:
	settings_(
		_settings
	),
	gui_(
		_gui
	),
	callbacks_(
		_callbacks
	),
	scoped_layout_(
		gui_.system(),
		sanguis::media_path()
		/ FCPPT_TEXT("gui")
		/ FCPPT_TEXT("main_menu.layout")
	),
	scoped_gui_sheet_(
		gui_.system(),
		scoped_layout_.window()
	),
	connect_button_(
		*scoped_layout_.window().getChild(
			"GroupBox/Connect"
		)
	),
	hostname_edit_(
		*scoped_layout_.window().getChild(
			"GroupBox/Hostname"
		)
	),
	port_edit_(
		*scoped_layout_.window().getChild(
			"GroupBox/Port"
		)
	),
	quickstart_connection_(
		scoped_layout_.window().getChild(
			"Quickstart"
		)
		->subscribeEvent(
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(
				std::bind(
					&object::handle_quickstart,
					this,
					std::placeholders::_1
				)
			)
		)
	),
	quit_connection_(
		scoped_layout_.window().getChild(
			"Quit"
		)
		->subscribeEvent(
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(
				std::bind(
					&object::handle_quit,
					this,
					std::placeholders::_1
				)
			)
		)
	),
	connect_connection_(
		connect_button_.subscribeEvent(
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(
				std::bind(
					&object::handle_connect,
					this,
					std::placeholders::_1
				)
			)
		)
	),
	hostname_change_connection_(
		hostname_edit_.subscribeEvent(
			CEGUI::Window::EventTextChanged,
			CEGUI::Event::Subscriber(
				std::bind(
					&object::handle_text_changed,
					this,
					std::placeholders::_1
				)
			)
		)
	),
	port_change_connection_(
		port_edit_.subscribeEvent(
			CEGUI::Window::EventTextChanged,
			CEGUI::Event::Subscriber(
				std::bind(
					&object::handle_text_changed,
					this,
					std::placeholders::_1
				)
			)
		)
	),
	connection_box_(
		fcppt::make_unique_ptr<
			sanguis::client::gui::menu::connection_box
		>(
			gui_,
			scoped_layout_.window(),
			std::bind(
				&menu::object::handle_cancel_connect,
				this
			),
			std::bind(
				&menu::object::handle_retry_connect,
				this
			)
		)
	)
{
	connect_button_.setEnabled(
		false
	);

	hostname_edit_.setText(
		sge::cegui::to_cegui_string(
			sge::parse::ini::get_or_create(
				_settings.sections(),
				config_section,
				config_hostname_key,
				sge::parse::ini::value(
					sge::parse::ini::string()
				)
			).get()
		)
	);

	port_edit_.setText(
		sge::cegui::to_cegui_string(
			sge::parse::ini::get_or_create(
				_settings.sections(),
				config_section,
				config_port_key,
				sge::parse::ini::value(
					sge::parse::ini::string()
				)
			).get()
		)
	);
}

sanguis::client::gui::menu::object::~object()
{
	sge::parse::ini::set_or_create(
		settings_.sections(),
		config_section,
		config_port_key,
		sge::parse::ini::value(
			sge::cegui::from_cegui_string(
				port_edit_.getText()
			)
		)
	);

	sge::parse::ini::set_or_create(
		settings_.sections(),
		config_section,
		config_hostname_key,
		sge::parse::ini::value(
			sge::cegui::from_cegui_string(
				hostname_edit_.getText()
			)
		)
	);
}

void
sanguis::client::gui::menu::object::process(
	sanguis::duration const &_delta
)
{
	gui_.update(
		_delta
	);
}

void
sanguis::client::gui::menu::object::draw(
	sge::renderer::context::ffp &_render_context
)
{
	_render_context.clear(
		sge::renderer::clear::parameters()
		.back_buffer(
			sge::image::color::predef::black()
		)
	);

	gui_.render(
		_render_context
	);
}

void
sanguis::client::gui::menu::object::connection_error(
	fcppt::string const &_message
)
{
	FCPPT_LOG_DEBUG(
		::logger,
		fcppt::log::_
			<< FCPPT_TEXT("got conection error: (")
			<< _message
			<< FCPPT_TEXT(')')
	);

	connection_box_->show_error(
		_message
	);
}

bool
sanguis::client::gui::menu::object::handle_quickstart(
	CEGUI::EventArgs const &
)
{
	callbacks_.quickstart()(
		alda::net::port(
			fcppt::extract_from_string_exn<
				alda::net::port::value_type
			>(
				sge::parse::ini::get_or_create(
					settings_.sections(),
					config_section,
					config_quickstart_port_key,
					sge::parse::ini::value(
						FCPPT_TEXT("31337")
					)
				).get()
			)
		)
	);

	return true;
}

bool
sanguis::client::gui::menu::object::handle_quit(
	CEGUI::EventArgs const &
)
{
	callbacks_.quit()();

	return true;
}

bool
sanguis::client::gui::menu::object::handle_connect(
	CEGUI::EventArgs const &
)
{
	connection_box_->activate();

	this->do_connect();

	return true;
}

bool
sanguis::client::gui::menu::object::handle_text_changed(
	CEGUI::EventArgs const &
)
{
	typedef unsigned long port_type;

	typedef fcppt::optional<
		port_type
	> optional_port;

	optional_port const opt_port(
		fcppt::extract_from_string<
			port_type
		>(
			sge::cegui::from_cegui_string(
				port_edit_.getText()
			)
		)
	);

	connect_button_.setEnabled(
		opt_port
		&&
		!hostname_edit_.getText().empty()
		&&
		(*opt_port > 0)
		&& (*opt_port < 65535)
	);

	return true;
}

void
sanguis::client::gui::menu::object::handle_cancel_connect()
{
	connection_box_->deactivate();

	callbacks_.cancel_connect()();
}

void
sanguis::client::gui::menu::object::handle_retry_connect()
{
	this->do_connect();
}

void
sanguis::client::gui::menu::object::do_connect()
{
	callbacks_.connect()(
		alda::net::host(
			fcppt::to_std_string(
				sge::cegui::from_cegui_string(
					hostname_edit_.getText()
				)
			)
		),
		alda::net::port(
			fcppt::extract_from_string_exn<
				alda::net::port::value_type
			>(
				sge::cegui::from_cegui_string(
					port_edit_.getText()
				)
			)
		)
	);
}
