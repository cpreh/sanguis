#ifndef SANGUIS_CLIENT_GUI_PERK_CHOOSER_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_PERK_CHOOSER_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/client/gui/perk/chooser_fwd.hpp>
#include <sanguis/client/gui/perk/state_fwd.hpp>
#include <sanguis/client/perk/state_fwd.hpp>
#include <sge/gui/context.hpp>
#include <sge/gui/master.hpp>
#include <sge/gui/background/colored.hpp>
#include <sge/gui/main_area/screen_corner.hpp>
#include <sge/gui/style/base_fwd.hpp>
#include <sge/gui/widget/box_container.hpp>
#include <sge/gui/widget/text.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/input/cursor/object_fwd.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/signal/scoped_connection.hpp>


namespace sanguis
{
namespace client
{
namespace gui
{
namespace perk
{

class chooser
{
	FCPPT_NONCOPYABLE(
		chooser
	);
public:
	chooser(
		sanguis::client::perk::state &,
		sge::gui::style::base const &,
		sge::renderer::device::ffp &,
		sge::viewport::manager &,
		sge::font::object &,
		sge::input::cursor::object &,
		sge::input::keyboard::device &
	);

	~chooser();

	void
	process(
		sanguis::duration const &
	);

	void
	draw(
		sge::renderer::context::ffp &
	);
private:
	void
	perks();

	void
	level();

	sge::font::string
	make_top_text() const;

	sanguis::client::perk::state &state_;

	sge::gui::style::base const &style_;

	sge::renderer::device::ffp &renderer_;

	sge::font::object &font_;

	sge::gui::context gui_context_;

	sge::gui::widget::text top_text_;

	typedef
	fcppt::unique_ptr<
		sanguis::client::gui::perk::state
	>
	state_unique_ptr;

	state_unique_ptr gui_state_;

	sge::gui::widget::box_container main_container_;

	sge::gui::main_area::screen_corner gui_area_;

	sge::gui::master gui_master_;

	sge::gui::background::colored gui_background_;

	fcppt::signal::scoped_connection const
		perk_connection_,
		level_connection_;
};

}
}
}
}

#endif
