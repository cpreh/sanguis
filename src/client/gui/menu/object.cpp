#include "object.hpp"
#include "connection_box.hpp"
#include "../object.hpp"
#include "../../log.hpp"
#include "../../../media_path.hpp"
#include "../../../net/port.hpp"
#include <sge/cegui/from_cegui_string.hpp>
#include <fcppt/io/istringstream.hpp>
#include <fcppt/log/parameters/inherited.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/lexical_cast.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/text.hpp>
#include <fcppt/to_std_string.hpp>
#include <CEGUI/elements/CEGUIPushButton.h>
#include <CEGUI/CEGUIWindowManager.h>
#include <CEGUI/CEGUIWindow.h>

namespace
{

fcppt::log::object mylogger(
	fcppt::log::parameters::inherited(
		sanguis::client::log(),
		FCPPT_TEXT("menu: object")
	)
);

}

sanguis::client::gui::menu::object::object(
	config::settings::object &_settings,
	client::gui::object &_gui,
	callbacks::object const &_callbacks
)
: 
	callbacks_(_callbacks),
	gui_(_gui),
	scoped_layout_(
		sanguis::media_path()
		/ FCPPT_TEXT("gui")
		/ FCPPT_TEXT("main_menu.layout"),
		_gui.charconv_system()
	),
	scoped_gui_sheet_(
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
			gui_.charconv_system(),
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
}

sanguis::client::gui::menu::object::~object()
{
}

void
sanguis::client::gui::menu::object::process(
	time_type const _delta
)
{
	gui_.update(
		_delta
	);

	gui_.render();
}

void
sanguis::client::gui::menu::object::connection_error(
	fcppt::string const &_message
)
{
	FCPPT_LOG_DEBUG(
		mylogger,
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
		31337 // FIXME!
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
