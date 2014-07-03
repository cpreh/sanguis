#ifndef SANGUIS_CLIENT_GUI_PERK_CHOOSER_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_PERK_CHOOSER_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/client/gui/perk/chooser_fwd.hpp>
#include <sanguis/client/gui/perk/state_fwd.hpp>
#include <sanguis/client/perk/state_fwd.hpp>
#include <sanguis/gui/context.hpp>
#include <sanguis/gui/master.hpp>
#include <sanguis/gui/screen_corner.hpp>
#include <sanguis/gui/widget/box_container.hpp>
#include <sanguis/gui/widget/text.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/input/cursor/object_fwd.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/scoped_connection.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


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

	sge::renderer::device::ffp &renderer_;

	sge::font::object &font_;

	sanguis::gui::context gui_context_;

	sanguis::gui::widget::text top_text_;

	typedef
	std::unique_ptr<
		sanguis::client::gui::perk::state
	>
	state_unique_ptr;

	state_unique_ptr gui_state_;

	sanguis::gui::widget::box_container main_container_;

	sanguis::gui::screen_corner gui_area_;

	sanguis::gui::master gui_master_;

	fcppt::signal::scoped_connection const
		perk_connection_,
		level_connection_;
};

}
}
}
}

#endif
