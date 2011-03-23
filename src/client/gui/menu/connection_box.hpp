#ifndef SANGUIS_CLIENT_GUI_MENU_CONNECTION_FWD_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_MENU_CONNECTION_FWD_HPP_INCLUDED

#include "callbacks/cancel_connect.hpp"
#include "callbacks/retry_connect.hpp"
#include "connection_box_fwd.hpp"
#include <sge/charconv/system_ptr.hpp>
#include <sge/cegui/toolbox/scoped_layout.hpp>
#include <fcppt/function/object.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/string.hpp>
#include <CEGUI/CEGUIEvent.h>

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
		sge::charconv::system_ptr,
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

	sge::charconv::system_ptr const charconv_system_;

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
