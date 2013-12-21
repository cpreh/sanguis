#ifndef SANGUIS_CLIENT_GUI_PERK_CHOOSER_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_PERK_CHOOSER_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/client/cursor/object_fwd.hpp>
#include <sanguis/client/gui/perk/chooser_fwd.hpp>
#include <sanguis/client/gui/perk/state_fwd.hpp>
#include <sanguis/client/perk/state_fwd.hpp>
#include <sanguis/gui/context.hpp>
#include <sanguis/gui/master.hpp>
#include <sanguis/gui/widget/box_container.hpp>
#include <sanguis/gui/widget/text.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/scoped_ptr_impl.hpp>
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
		sanguis::client::cursor::object &,
		sanguis::client::perk::state &,
		sge::renderer::device::ffp &,
		sge::viewport::manager &,
		sge::font::object &,
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

	void
	update_top_text();

	sanguis::client::perk::state &state_;

	sge::renderer::device::ffp &renderer_;

	sge::font::object &font_;

	sanguis::gui::context gui_context_;

	sanguis::gui::widget::text top_text_;

	sanguis::gui::widget::box_container main_container_;

	sanguis::gui::master gui_master_;

	typedef
	fcppt::scoped_ptr<
		sanguis::client::gui::perk::state
	>
	state_scoped_ptr;

	state_scoped_ptr gui_state_;

	fcppt::signal::scoped_connection const
		perk_connection_,
		level_connection_;
};

}
}
}
}

#endif
