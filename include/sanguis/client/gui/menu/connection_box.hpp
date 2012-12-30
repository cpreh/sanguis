#ifndef SANGUIS_CLIENT_GUI_MENU_CONNECTION_BOX_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_MENU_CONNECTION_BOX_HPP_INCLUDED

#include <sanguis/client/gui/menu/callbacks/cancel_connect.hpp>
#include <sanguis/client/gui/menu/callbacks/retry_connect.hpp>
#include <sanguis/client/gui/menu/connection_box_fwd.hpp>
#include <sanguis/client/gui/object_fwd.hpp>
#include <sge/charconv/system_fwd.hpp>
#include <sge/cegui/toolbox/scoped_layout.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/string.hpp>
#include <fcppt/config/external_begin.hpp>
#include <CEGUI/Event.h>
#include <fcppt/config/external_end.hpp>

namespace CEGUI
{
class EventArgs;
class Window;
}

namespace sanguis
{
namespace client
{
namespace gui
{
namespace menu
{

class connection_box
{
	FCPPT_NONCOPYABLE(
		connection_box
	);
public:
	connection_box(
		client::gui::object &,
		CEGUI::Window &parent_window,
		callbacks::cancel_connect const &,
		callbacks::retry_connect const &
	);

	~connection_box();

	void
	show_error(
		fcppt::string const &
	);

	void
	activate();

	void
	deactivate();
private:
	bool
	handle_cancel_connect(
		CEGUI::EventArgs const &
	);

	bool
	handle_retry_connect(
		CEGUI::EventArgs const &
	);

	sge::charconv::system &charconv_system_;

	callbacks::cancel_connect const cancel_connect_;

	callbacks::retry_connect const retry_connect_;

	sge::cegui::toolbox::scoped_layout const scoped_layout_;

	CEGUI::Window
		&root_window_,
		&cancel_button_,
		&retry_button_,
		&message_text_;

	CEGUI::Event::ScopedConnection const
		cancel_connect_connection_,
		retry_connect_connection_;
};

}
}
}
}

#endif
