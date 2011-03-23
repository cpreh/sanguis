#include "object.hpp"
#include "connection_box.hpp"
#include "../object.hpp"
#include "../../log.hpp"
#include "../../../media_path.hpp"
#include <sge/cegui/from_cegui_string.hpp>
#include <fcppt/log/parameters/inherited.hpp>
#include <fcppt/log/object.hpp>
#include <fcppt/log/headers.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
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
	scoped_gui_sheet_(
		scoped_layout_.window()
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
		CEGUI::WindowManager::getSingleton().getWindow(
			"MainMenu/FrameWindow/Connect"
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
		sge::cegui::from_cegui_string(
			CEGUI::WindowManager::getSingleton().getWindow(
				"MainMenu/FrameWindow/Hostname"
			)
			->getText(),
			gui_.charconv_system()
		),
		sge::cegui::from_cegui_string(
			CEGUI::WindowManager::getSingleton().getWindow(
				"MainMenu/FrameWindow/Port"
			)
			->getText(),
			gui_.charconv_system()
		)
	);
}
