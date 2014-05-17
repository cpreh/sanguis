#ifndef SANGUIS_CLIENT_GUI_MENU_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_MENU_OBJECT_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/client/gui/menu/resolution_chooser.hpp>
#include <sanguis/client/gui/menu/callbacks/object.hpp>
#include <sanguis/client/config/settings/object_fwd.hpp>
#include <sanguis/gui/context.hpp>
#include <sanguis/gui/master.hpp>
#include <sanguis/gui/viewport_adaptor.hpp>
#include <sanguis/gui/widget/box_container.hpp>
#include <sanguis/gui/widget/button.hpp>
#include <sanguis/gui/widget/edit.hpp>
#include <sanguis/gui/widget/frame.hpp>
#include <sanguis/gui/widget/static_text.hpp>
#include <sanguis/gui/widget/text.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/input/cursor/object_fwd.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/renderer/system_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/renderer/device/index_fwd.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/string.hpp>
#include <fcppt/signal/scoped_connection.hpp>


namespace sanguis
{
namespace client
{
namespace gui
{
namespace menu
{

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	object(
		sge::renderer::system const &,
		sge::renderer::device::ffp &,
		sge::renderer::device::index,
		sge::viewport::manager &,
		sge::font::object &,
		sge::input::cursor::object &,
		sge::input::keyboard::device &,
		sanguis::client::config::settings::object &,
		sanguis::client::gui::menu::callbacks::object const &
	);

	~object();

	void
	process(
		sanguis::duration const &
	);

	void
	draw(
		sge::renderer::context::ffp &
	);

	void
	connection_error(
		fcppt::string const &
	);

	fcppt::string
	player_name() const;
private:
	void
	handle_quickstart();

	void
	handle_text_changed();

	void
	handle_connect();

	sanguis::client::config::settings::object &settings_;

	sanguis::gui::context gui_context_;

	sanguis::client::gui::menu::callbacks::object const callbacks_;

		sanguis::gui::widget::button quickstart_button_;

		sanguis::client::gui::menu::resolution_chooser resolution_chooser_;

			sanguis::gui::widget::static_text player_name_label_;

			sanguis::gui::widget::edit player_name_edit_;

		sanguis::gui::widget::box_container player_name_line_;

					sanguis::gui::widget::static_text hostname_label_;

					sanguis::gui::widget::edit hostname_edit_;

				sanguis::gui::widget::box_container hostname_line_;

					sanguis::gui::widget::static_text port_label_;

					sanguis::gui::widget::edit port_edit_;

				sanguis::gui::widget::box_container port_line_;

				sanguis::gui::widget::text connect_text_;

				sanguis::gui::widget::button connect_button_;

			sanguis::gui::widget::box_container connect_box_;

		sanguis::gui::widget::frame connect_frame_;

		sanguis::gui::widget::button quit_button_;

	sanguis::gui::widget::box_container main_container_;

	sanguis::gui::master gui_master_;

	sanguis::gui::viewport_adaptor viewport_adaptor_;

	fcppt::signal::scoped_connection const
		quickstart_connection_,
		connect_connection_,
		quit_connection_,
		hostname_change_connection_,
		port_change_connection_;
};

}
}
}
}

#endif
