#ifndef SANGUIS_CLIENT_GUI_PERK_LINE_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_PERK_LINE_HPP_INCLUDED

#include <sanguis/perk_type.hpp>
#include <sanguis/client/gui/perk/line_fwd.hpp>
#include <sanguis/client/perk/info_fwd.hpp>
#include <sanguis/client/perk/state_fwd.hpp>
#include <sanguis/gui/context_fwd.hpp>
#include <sanguis/gui/widget/box_container.hpp>
#include <sanguis/gui/widget/button.hpp>
#include <sanguis/gui/widget/text.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/image/color/any/object_fwd.hpp>
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
		sanguis::gui::context &,
		sanguis::client::perk::state &,
		sanguis::client::perk::info const &
	);

	~line();

	sanguis::gui::widget::box_container &
	widget();
private:
	void
	on_click();

	void
	on_level_change();

	sge::image::color::any::object const
	text_color() const;

	sanguis::perk_type const perk_type_;

	sanguis::client::perk::state &state_;

	sanguis::gui::widget::button button_;

	sanguis::gui::widget::text text_;

	sanguis::gui::widget::box_container box_;

	fcppt::signal::scoped_connection const click_connection_;

	fcppt::signal::scoped_connection const level_change_connection_;
};

}
}
}
}

#endif
