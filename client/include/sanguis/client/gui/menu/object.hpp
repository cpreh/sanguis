#ifndef SANGUIS_CLIENT_GUI_MENU_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_MENU_OBJECT_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/client/config/settings/object_ref.hpp>
#include <sanguis/client/gui/menu/resolution_chooser.hpp>
#include <sanguis/client/gui/menu/callbacks/object.hpp>
#include <sge/font/object_ref.hpp>
#include <sge/gui/context.hpp>
#include <sge/gui/master.hpp>
#include <sge/gui/background/colored.hpp>
#include <sge/gui/main_area/viewport_adaptor.hpp>
#include <sge/gui/style/const_reference.hpp>
#include <sge/gui/widget/box_container.hpp>
#include <sge/gui/widget/button.hpp>
#include <sge/gui/widget/edit.hpp>
#include <sge/gui/widget/frame.hpp>
#include <sge/gui/widget/static_text.hpp>
#include <sge/gui/widget/text.hpp>
#include <sge/input/event_base_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <sge/viewport/manager_ref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/string.hpp>
#include <fcppt/signal/auto_connection.hpp>


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
	FCPPT_NONMOVABLE(
		object
	);
public:
	object(
		sge::renderer::device::ffp_ref,
		sge::viewport::manager_ref,
		sge::font::object_ref,
		sanguis::client::config::settings::object_ref,
		sanguis::client::gui::menu::callbacks::object &&,
		sge::gui::style::const_reference
	);

	~object();

	void
	process(
		sanguis::duration const &
	);

	void
	draw(
		sge::renderer::context::ffp & // NOLINT(google-runtime-references)
	); // NOLINT(google-runtime-references)

	void
	connection_error(
		fcppt::string const &
	);

	void
	input(
		sge::input::event_base const &
	);

	[[nodiscard]]
	fcppt::string
	player_name() const;
private:
	void
	handle_quickstart();

	void
	handle_text_changed();

	void
	handle_connect();

	sanguis::client::config::settings::object_ref const settings_;

	sge::renderer::device::ffp_ref const renderer_;

	sge::gui::context gui_context_;

	sanguis::client::gui::menu::callbacks::object const callbacks_;

		sge::gui::widget::button quickstart_button_;

		sanguis::client::gui::menu::resolution_chooser resolution_chooser_;

			sge::gui::widget::static_text player_name_label_;

			sge::gui::widget::edit player_name_edit_;

		sge::gui::widget::box_container player_name_line_;

					sge::gui::widget::static_text hostname_label_;

					sge::gui::widget::edit hostname_edit_;

				sge::gui::widget::box_container hostname_line_;

					sge::gui::widget::static_text port_label_;

					sge::gui::widget::edit port_edit_;

				sge::gui::widget::box_container port_line_;

				sge::gui::widget::text connect_text_;

				sge::gui::widget::button connect_button_;

			sge::gui::widget::box_container connect_box_;

		sge::gui::widget::frame connect_frame_;

		sge::gui::widget::button quit_button_;

	sge::gui::widget::box_container main_container_;

	sge::gui::main_area::viewport_adaptor gui_area_;

	sge::gui::master gui_master_;

	sge::gui::background::colored gui_background_;

	bool connect_running_;

	fcppt::signal::auto_connection const quickstart_connection_;
	fcppt::signal::auto_connection const connect_connection_;
	fcppt::signal::auto_connection const quit_connection_;
	fcppt::signal::auto_connection const hostname_change_connection_;
	fcppt::signal::auto_connection const port_change_connection_;
};

}
}
}
}

#endif
