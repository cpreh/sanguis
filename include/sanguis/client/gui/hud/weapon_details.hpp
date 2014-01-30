#ifndef SANGUIS_CLIENT_GUI_HUD_WEAPON_DETAILS_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_HUD_WEAPON_DETAILS_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/optional_weapon_description_fwd.hpp>
#include <sanguis/client/gui/hud/weapon_details_fwd.hpp>
#include <sanguis/client/gui/hud/weapon_tooltip_unique_ptr.hpp>
#include <sanguis/gui/context.hpp>
#include <sanguis/gui/master.hpp>
#include <sanguis/gui/minimum_size_area.hpp>
#include <sanguis/gui/widget/box_container.hpp>
#include <sanguis/load/hud/context_fwd.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/input/cursor/object_fwd.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/rucksack/rect_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace gui
{
namespace hud
{

class weapon_details
{
	FCPPT_NONCOPYABLE(
		weapon_details
	);
public:
	weapon_details(
		sanguis::load::hud::context &,
		sge::renderer::device::ffp &,
		sge::font::object &,
		sge::input::keyboard::device &,
		sge::input::cursor::object &,
		sanguis::optional_weapon_description const &,
		sanguis::optional_weapon_description const &,
		sge::rucksack::rect
	);

	~weapon_details();

	void
	update(
		sanguis::duration const &
	);

	void
	draw(
		sge::renderer::context::ffp &
	);
private:
	sanguis::gui::context gui_context_;

	typedef
	std::vector<
		sanguis::client::gui::hud::weapon_tooltip_unique_ptr
	>
	tooltip_vector;

	tooltip_vector tooltips_;

	sanguis::gui::widget::box_container container_;

	sanguis::gui::master gui_master_;

	sanguis::gui::minimum_size_area gui_area_;
};

}
}
}
}

#endif
