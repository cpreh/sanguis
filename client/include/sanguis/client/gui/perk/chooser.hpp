#ifndef SANGUIS_CLIENT_GUI_PERK_CHOOSER_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_PERK_CHOOSER_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/client/gui/perk/chooser_fwd.hpp>
#include <sanguis/client/gui/perk/state_fwd.hpp>
#include <sanguis/client/perk/state_ref.hpp>
#include <sge/font/object_ref.hpp>
#include <sge/font/string.hpp>
#include <sge/gui/context.hpp>
#include <sge/gui/master.hpp>
#include <sge/gui/background/colored.hpp>
#include <sge/gui/main_area/screen_corner.hpp>
#include <sge/gui/style/const_reference.hpp>
#include <sge/gui/widget/box_container.hpp>
#include <sge/gui/widget/text.hpp>
#include <sge/input/event_base_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <sge/viewport/manager_ref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/signal/auto_connection.hpp>


namespace sanguis::client::gui::perk
{

class chooser
{
	FCPPT_NONMOVABLE(
		chooser
	);
public:
	chooser(
		sanguis::client::perk::state_ref,
		sge::gui::style::const_reference,
		sge::renderer::device::ffp_ref,
		sge::viewport::manager_ref,
		sge::font::object_ref
	);

	~chooser();

	void
	process(
		sanguis::duration const &
	);

	void
	draw(
		sge::renderer::context::ffp & // NOLINT(google-runtime-references)
	); // NOLINT(google-runtime-references)

	void
	input(
		sge::input::event_base const &
	);
private:
	void
	perks();

	void
	level();

	[[nodiscard]]
	sge::font::string
	make_top_text() const;

	sanguis::client::perk::state_ref const state_;

	sge::gui::style::const_reference const style_;

	sge::renderer::device::ffp_ref const renderer_;

	sge::font::object_ref const font_;

	sge::gui::context gui_context_;

	sge::gui::widget::text top_text_;

	using
	state_unique_ptr
	=
	fcppt::unique_ptr<
		sanguis::client::gui::perk::state
	>;

	state_unique_ptr gui_state_;

	sge::gui::widget::box_container main_container_;

	sge::gui::main_area::screen_corner gui_area_;

	sge::gui::master gui_master_;

	sge::gui::background::colored gui_background_;

	fcppt::signal::auto_connection const perk_connection_;
	fcppt::signal::auto_connection const level_connection_;
};

}

#endif
