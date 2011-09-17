#include "object.hpp"
#include "connection_box.hpp"
#include "../object.hpp"
#include "../../config/settings/get_or_default.hpp"
#include "../../config/settings/set_key.hpp"
#include "../../log_location.hpp"
#include "../../../log_parameters.hpp"
#include "../../../media_path.hpp"
#include "../../../net/port.hpp"
#include <sge/cegui/from_cegui_string.hpp>
#include <sge/cegui/to_cegui_string.hpp>
#include <fcppt/io/istringstream.hpp>
#include <fcppt/log/parameters/all.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/log/location.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/lexical_cast.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/to_std_string.hpp>
#include <elements/CEGUIPushButton.h>
#include <CEGUIWindowManager.h>
#include <CEGUIWindow.h>

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

fcppt::string const
	config_section(
		FCPPT_TEXT("gui_menu")
	),
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
	settings_(_settings),
	gui_(_gui),
	callbacks_(_callbacks),
	scoped_layout_(
		gui_.system(),
		sanguis::media_path()
		/ FCPPT_TEXT("gui")
		/ FCPPT_TEXT("main_menu.layout"),
		_gui.charconv_system()
	),
	scoped_gui_sheet_(
		gui_.system(),
		scoped_layout_.window()
	),
	connect_button_(
		*CEGUI::WindowManager::getSingleton().getWindow(
			"MainMenu/FrameWindow/Connect"
		)
	),
	hostname_edit_(
		*CEGUI::WindowManager::getSingleton().getWindow(
			"MainMenu/FrameWindow/Hostname"
		)
	),
	port_edit_(
		*CEGUI::WindowManager::getSingleton().getWindow(
			"MainMenu/FrameWindow/Port"
		)
	),
	quickstart_connection_(
		CEGUI::WindowManager::getSingleton().getWindow(
			"MainMenu/FrameWindow/Quickstart"
		)
		->subscribeEvent(
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(
				std::tr1::bind(
					&object::handle_quickstart,
					this,
					std::tr1::placeholders::_1
				)
			)
		)
	),
	quit_connection_(
		CEGUI::WindowManager::getSingleton().getWindow(
			"MainMenu/FrameWindow/Quit"
		)
		->subscribeEvent(
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(
				std::tr1::bind(
					&object::handle_quit,
					this,
					std::tr1::placeholders::_1
				)
			)
		)
	),
	connect_connection_(
		connect_button_.subscribeEvent(
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(
				std::tr1::bind(
					&object::handle_connect,
					this,
					std::tr1::placeholders::_1
				)
			)
		)
	),
	hostname_change_connection_(
		hostname_edit_.subscribeEvent(
			CEGUI::Window::EventTextChanged,
			CEGUI::Event::Subscriber(
				std::tr1::bind(
					&object::handle_text_changed,
					this,
					std::tr1::placeholders::_1
				)
			)
		)
	),
	port_change_connection_(
		port_edit_.subscribeEvent(
			CEGUI::Window::EventTextChanged,
			CEGUI::Event::Subscriber(
				std::tr1::bind(
					&object::handle_text_changed,
					this,
					std::tr1::placeholders::_1
				)
			)
		)
	),
	connection_box_(
		fcppt::make_unique_ptr<
			menu::connection_box
		>(
			fcppt::ref(
				gui_
			),
			fcppt::ref(
				*CEGUI::WindowManager::getSingleton().getWindow(
					"MainMenu/FrameWindow"
				)
			),
			std::tr1::bind(
				&menu::object::handle_cancel_connect,
				this
			),
			std::tr1::bind(
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
			client::config::settings::get_or_default(
				_settings,
				config_section,
				config_hostname_key,
				FCPPT_TEXT("")
			),
			gui_.charconv_system()
		)
	);

	port_edit_.setText(
		sge::cegui::to_cegui_string(
			client::config::settings::get_or_default(
				_settings,
				config_section,
				config_port_key,
				FCPPT_TEXT("")
			),
			gui_.charconv_system()
		)
	);
}

sanguis::client::gui::menu::object::~object()
{
	client::config::settings::set_key(
		settings_,
		config_section,
		config_port_key,
		sge::cegui::from_cegui_string(
			port_edit_.getText(),
			gui_.charconv_system()
		)
	);

	client::config::settings::set_key(
		settings_,
		config_section,
		config_hostname_key,
		sge::cegui::from_cegui_string(
			hostname_edit_.getText(),
			gui_.charconv_system()
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
sanguis::client::gui::menu::object::draw()
{
	gui_.render();
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
		fcppt::lexical_cast<
			net::port
		>(
			client::config::settings::get_or_default(
				settings_,
				config_section,
				config_quickstart_port_key,
				FCPPT_TEXT("31337")
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
	// TODO: we should create a lexical_cast that returns an optional
	fcppt::io::istringstream stream(
		sge::cegui::from_cegui_string(
			port_edit_.getText(),
			gui_.charconv_system()
		)
	);

	unsigned long port;

	bool const convert_success(
		(stream >> port)
		&& stream.eof()
	);

	connect_button_.setEnabled(
		convert_success
		&&
		!hostname_edit_.getText().empty()
		&&
		(port > 0)
		&& (port < 65535)
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
		fcppt::to_std_string(
			sge::cegui::from_cegui_string(
				hostname_edit_.getText(),
				gui_.charconv_system()
			)
		),
		fcppt::lexical_cast<
			net::port
		>(
			sge::cegui::from_cegui_string(
				port_edit_.getText(),
				gui_.charconv_system()
			)
		)
	);
}
