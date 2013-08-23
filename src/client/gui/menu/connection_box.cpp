#include <sanguis/media_path.hpp>
#include <sanguis/client/gui/object.hpp>
#include <sanguis/client/gui/menu/connection_box.hpp>
#include <sanguis/client/gui/menu/callbacks/cancel_connect.hpp>
#include <sanguis/client/gui/menu/callbacks/retry_connect.hpp>
#include <sge/cegui/to_cegui_string.hpp>
#include <fcppt/string.hpp>
#include <fcppt/text.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/Window.h>
#include <CEGUI/widgets/PushButton.h>
#include <functional>
#include <fcppt/config/external_end.hpp>


sanguis::client::gui::menu::connection_box::connection_box(
	sanguis::client::gui::object &_gui,
	CEGUI::Window &_parent_window,
	sanguis::client::gui::menu::callbacks::cancel_connect const &_cancel_connect,
	sanguis::client::gui::menu::callbacks::retry_connect const &_retry_connect
)
:
	cancel_connect_(
		_cancel_connect
	),
	retry_connect_(
		_retry_connect
	),
	scoped_layout_(
		_gui.system(),
		sanguis::media_path()
		/
		FCPPT_TEXT("gui")
		/
		FCPPT_TEXT("connection_box.layout")
	),
	root_window_(
		scoped_layout_.window()
	),
	cancel_button_(
		*root_window_.getChild(
			"Cancel"
		)
	),
	retry_button_(
		*root_window_.getChild(
			"Retry"
		)
	),
	message_text_(
		*root_window_.getChild(
			"MessageText"
		)
	),
	cancel_connect_connection_(
		cancel_button_.subscribeEvent(
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(
				std::bind(
					&sanguis::client::gui::menu::connection_box::handle_cancel_connect,
					this,
					std::placeholders::_1
				)
			)
		)
	),
	retry_connect_connection_(
		retry_button_.subscribeEvent(
			CEGUI::PushButton::EventClicked,
			CEGUI::Event::Subscriber(
				std::bind(
					&sanguis::client::gui::menu::connection_box::handle_retry_connect,
					this,
					std::placeholders::_1
				)
			)
		)
	)
{
	_parent_window.addChild(
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
			_message
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
			FCPPT_TEXT("Connecting...")
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
			FCPPT_TEXT("Retrying...")
		)
	);

	retry_connect_();

	return true;
}
