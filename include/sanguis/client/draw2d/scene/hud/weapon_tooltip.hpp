#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_HUD_WEAPON_TOOLTIP_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_HUD_WEAPON_TOOLTIP_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/weapon_description_fwd.hpp>
#include <sanguis/client/draw2d/scene/hud/weapon_tooltip_fwd.hpp>
#include <sanguis/gui/context.hpp>
#include <sanguis/gui/master.hpp>
#include <sanguis/gui/minimum_size_area.hpp>
#include <sanguis/gui/widget/box_container.hpp>
#include <sanguis/gui/widget/text.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/input/cursor/object_fwd.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <vector>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace draw2d
{
namespace scene
{
namespace hud
{

class weapon_tooltip
{
	FCPPT_NONCOPYABLE(
		weapon_tooltip
	);
public:
	weapon_tooltip(
		sge::renderer::device::ffp &,
		sge::font::object &,
		sge::input::keyboard::device &,
		sge::input::cursor::object &,
		sanguis::weapon_description const &
	);

	~weapon_tooltip();

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

	sanguis::gui::widget::text name_text_;

	typedef
	std::unique_ptr<
		sanguis::gui::widget::text
	>
	text_unique_ptr;

	typedef
	std::vector<
		text_unique_ptr
	>
	text_unique_ptr_vector;

	text_unique_ptr_vector attribute_texts_;

	sanguis::gui::widget::box_container container_;

	sanguis::gui::master gui_master_;

	sanguis::gui::minimum_size_area gui_area_;
};

}
}
}
}
}

#endif
