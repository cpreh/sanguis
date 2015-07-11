#ifndef SANGUIS_CLIENT_GUI_PERK_LINE_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_PERK_LINE_HPP_INCLUDED

#include <sanguis/perk_type.hpp>
#include <sanguis/client/gui/perk/line_fwd.hpp>
#include <sanguis/client/perk/info_fwd.hpp>
#include <sanguis/client/perk/state_fwd.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/gui/context_fwd.hpp>
#include <sge/gui/text_color_fwd.hpp>
#include <sge/gui/style/base_fwd.hpp>
#include <sge/gui/widget/box_container.hpp>
#include <sge/gui/widget/button.hpp>
#include <sge/gui/widget/text.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/signal/scoped_connection.hpp>


namespace sanguis
{
namespace client
{
namespace gui
{
namespace perk
{

class line
{
	FCPPT_NONCOPYABLE(
		line
	);
public:
	line(
		sge::renderer::device::ffp &,
		sge::font::object &,
		sge::gui::context &,
		sge::gui::style::base const &,
		sanguis::client::perk::state &,
		sanguis::client::perk::info const &
	);

	~line();

	sge::gui::widget::box_container &
	widget();
private:
	void
	on_click();

	void
	on_level_change();

	sge::gui::text_color
	text_color() const;

	sanguis::perk_type const perk_type_;

	sanguis::client::perk::state &state_;

	sge::gui::widget::button button_;

	sge::gui::widget::text text_;

	sge::gui::widget::box_container box_;

	fcppt::signal::scoped_connection const click_connection_;

	fcppt::signal::scoped_connection const level_change_connection_;
};

}
}
}
}

#endif
