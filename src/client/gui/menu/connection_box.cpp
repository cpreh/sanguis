#include <sanguis/client/gui/menu/connection_box.hpp>
#include <sanguis/client/gui/object.hpp>
#include <sanguis/media_path.hpp>
#include <sge/cegui/to_cegui_string.hpp>
#include <fcppt/tr1/functional.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/WindowManager.h>
#include <CEGUI/Window.h>
#include <CEGUI/widgets/PushButton.h>
#include <fcppt/config/external_end.hpp>

sanguis::client::gui::menu::connection_box::connection_box(
	client::gui::object &_gui,
	CEGUI::Window &_parent_window,
	callbacks::cancel_connect const &_cancel_connect,
	callbacks::retry_connect const &_retry_connect
)
:
	charconv_system_(
		_gui.charconv_system()
	),
	cancel_connect_(_cancel_connect),
	retry_connect_(_retry_connect),
	scoped_layout_(
		_gui.system(),
		sanguis::media_path()
		/ FCPPT_TEXT("gui")
		/ FCPPT_TEXT("connection_box.layout")
	),
	root_window_(
		*CEGUI::WindowManager::getSingleton().getWindow(
			"ConnectionBox"
		)
	),
	cancel_button_(
		*CEGUI::WindowManager::getSingleton().getWindow(
			"ConnectionBox/Cancel"
		)
	),
	retry_button_(
		*CEGUI::WindowManager::getSingleton().getWindow(
			"ConnectionBox/Retry"
		)
	),
	message_text_(
		*CEGUI::WindowManager::getSingleton().getWindow(
			"ConnectionBox/MessageText"
		)
	),
	cancel_connect_connection_(
		cancel_button_.subscribeEvent(
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(
				std::tr1::bind(
					&connection_box::handle_cancel_connect,
					this,
					std::tr1::placeholders::_1
				)
			)
		)
	),
	retry_connect_connection_(
		retry_button_.subscribeEvent(
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(
				std::tr1::bind(
					&connection_box::handle_retry_connect,
					this,
					std::tr1::placeholders::_1
				)
			)
		)
	)
{
	_parent_window.addChildWindow(
		&root_window_
	);

	root_window_.setVisible(
		false
	);
}

sanguis::client::gui::menu::connection_box::~connection_box()
{
}

void
sanguis::client::gui::menu::connection_box::show_error(
	fcppt::string const &_message
)
{
	message_text_.setText(
		sge::cegui::to_cegui_string(
			_message,
			charconv_system_
		)
	);

	retry_button_.setEnabled(
		true
	);
}

void
sanguis::client::gui::menu::connection_box::activate()
{
	root_window_.setModalState(
		true
	);

	retry_button_.setEnabled(
		false
	);

	root_window_.setVisible(
		true
	);

	message_text_.setText(
		sge::cegui::to_cegui_string(
			FCPPT_TEXT("Connecting..."),
			charconv_system_
		)
	);
}

void
sanguis::client::gui::menu::connection_box::deactivate()
{
	root_window_.setModalState(
		false
	);

	root_window_.setVisible(
		false
	);
}

bool
sanguis::client::gui::menu::connection_box::handle_cancel_connect(
	CEGUI::EventArgs const &
)
{
	cancel_connect_();

	return true;
}

bool
sanguis::client::gui::menu::connection_box::handle_retry_connect(
	CEGUI::EventArgs const &
)
{
	retry_button_.setEnabled(
		false
	);

	message_text_.setText(
		sge::cegui::to_cegui_string(
			FCPPT_TEXT("Retrying..."),
			charconv_system_
		)
	);

	retry_connect_();

	return true;
}
