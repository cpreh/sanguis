#ifndef SANGUIS_CLIENT_GUI_PERK_LINE_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_PERK_LINE_HPP_INCLUDED

#include <sanguis/perk_type.hpp>
#include <sanguis/client/gui/perk/line_fwd.hpp>
#include <sanguis/client/perk/info_fwd.hpp>
#include <sanguis/client/perk/state_ref.hpp>
#include <sge/font/object_ref.hpp>
#include <sge/gui/context_ref.hpp>
#include <sge/gui/text_color_fwd.hpp>
#include <sge/gui/style/const_reference.hpp>
#include <sge/gui/widget/box_container.hpp>
#include <sge/gui/widget/button.hpp>
#include <sge/gui/widget/text.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/signal/auto_connection.hpp>


namespace sanguis::client::gui::perk
{

class line
{
	FCPPT_NONMOVABLE(
		line
	);
public:
	line(
		sge::renderer::device::ffp_ref,
		sge::font::object_ref,
		sge::gui::context_ref,
		sge::gui::style::const_reference,
		sanguis::client::perk::state_ref,
		sanguis::client::perk::info const &
	);

	~line();

	[[nodiscard]]
	sge::gui::widget::box_container &
	widget();
private:
	void
	on_click();

	void
	on_level_change();

	[[nodiscard]]
	sge::gui::text_color
	text_color() const;

	sanguis::perk_type const perk_type_;

	sanguis::client::perk::state_ref const state_;

	sge::gui::widget::button button_;

	sge::gui::widget::text text_;

	sge::gui::widget::box_container box_;

	fcppt::signal::auto_connection const click_connection_;

	fcppt::signal::auto_connection const level_change_connection_;
};

}

#endif
