#ifndef SANGUIS_CLIENT_GUI_HUD_WEAPON_WIDGET_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_HUD_WEAPON_WIDGET_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/duration.hpp>
#include <sanguis/magazine_remaining.hpp>
#include <sanguis/weapon_description.hpp>
#include <sanguis/client/gui/hud/weapon_widget_fwd.hpp>
#include <sanguis/client/load/hud/context_fwd.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/gui/context_fwd.hpp>
#include <sge/gui/style/base_fwd.hpp>
#include <sge/gui/widget/bar.hpp>
#include <sge/gui/widget/box_container.hpp>
#include <sge/gui/widget/image.hpp>
#include <sge/gui/widget/text.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <fcppt/noncopyable.hpp>


namespace sanguis
{
namespace client
{
namespace gui
{
namespace hud
{

class weapon_widget
{
	FCPPT_NONCOPYABLE(
		weapon_widget
	);
public:
	weapon_widget(
		sanguis::diff_clock const &,
		sanguis::client::load::hud::context &,
		sge::gui::context &,
		sge::gui::style::base const &,
		sge::renderer::device::ffp &,
		sge::font::object &,
		sanguis::weapon_description const &
	);

	~weapon_widget();

	void
	magazine_remaining(
		sanguis::magazine_remaining
	);

	void
	reload_time(
		sanguis::duration
	);

	void
	update();

	sge::gui::widget::box_container &
	widget();

	sanguis::weapon_description const &
	weapon_description() const;
private:
	sge::font::string
	make_text(
		sanguis::magazine_remaining
	) const;

	sanguis::weapon_description const description_;

	sanguis::diff_timer reload_time_;

	sge::gui::widget::image image_;

	sge::gui::widget::text text_;

	sge::gui::widget::bar cooldown_bar_;

	sge::gui::widget::box_container container_;
};

}
}
}
}

#endif
