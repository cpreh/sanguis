#include "object.hpp"
#include "../object.hpp"
#include "../../log.hpp"
#include "../../../media_path.hpp"
#include <sge/cegui/from_cegui_string.hpp>
#include <fcppt/log/parameters/inherited.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/text.hpp>
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
	quickstart_connection_(
		CEGUI::WindowManager::getSingleton().getWindow(
			"Root/FrameWindow/Quickstart"
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
			"Root/FrameWindow/Quit"
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
		CEGUI::WindowManager::getSingleton().getWindow(
			"Root/FrameWindow/Connect"
		)
		->subscribeEvent(
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(
				std::tr1::bind(
					&object::handle_connect,
					this,
					std::tr1::placeholders::_1
				)
			)
		)
	)
{
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
#if 0
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_
			<< FCPPT_TEXT("got conection error: (")
			<< _message 
			<< FCPPT_TEXT(")")
	);

	connect_box_.label_.text(
		sge::font::text::from_fcppt_string(
			FCPPT_TEXT("Connection to \"")+
			connection_host_+
			FCPPT_TEXT("\" on port \"")+
			connection_port_+
			FCPPT_TEXT("\" failed: \n")+
			_message
		)
	);
#endif
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
	callbacks_.connect()(
		sge::cegui::from_cegui_string(
			CEGUI::WindowManager::getSingleton().getWindow(
				"Root/FrameWindow/Hostname"
			)
			->getText(),
			gui_.charconv_system()
		),
		sge::cegui::from_cegui_string(
			CEGUI::WindowManager::getSingleton().getWindow(
				"Root/FrameWindow/Port"
			)
			->getText(),
			gui_.charconv_system()
		)
	);

	return true;
}

#if 0
void
sanguis::client::gui::menu::object::connect_from_menu()
{
	this->connect(
		sge::font::text::to_fcppt_string(
			connect_.host_edit.text()
		),
		sge::font::text::to_fcppt_string(
			connect_.port_edit.text()
		)
	);
}
#endif

#if 0
void
sanguis::client::gui::menu::object::connect()
{
	FCPPT_LOG_DEBUG(
		mylogger,
		fcppt::log::_
			<< FCPPT_TEXT("connecting to ")
			<< _host 
			<< FCPPT_TEXT(" on port ")
			<< _port
	);

	connection_host_ = _host;
	connection_port_ = _port;

	connect_box_.label_.text(
		sge::font::text::from_fcppt_string(
			FCPPT_TEXT("Connecting to \"")+
			_host+
			FCPPT_TEXT("\" on port \"")+
			_port+
			FCPPT_TEXT("\"")
		)
	);

	callbacks_.connect_(
		_host,
		_port
	);
	
	mover_.reset(
		connect_box_.parent
	);
}
#endif

#if 0
void
sanguis::client::gui::menu::object::cancel_connect()
{
	mover_.reset(
		connect_.parent
	);
	callbacks_.cancel_connect()();
}
#endif	
