#ifndef SANGUIS_CLIENT_DRAW2D_SCENE_HUD_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_DRAW2D_SCENE_HUD_OBJECT_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/is_primary_weapon.hpp>
#include <sanguis/optional_weapon_description.hpp>
#include <sanguis/weapon_description_fwd.hpp>
#include <sanguis/client/draw2d/scene/hud/object_fwd.hpp>
#include <sanguis/client/exp.hpp>
#include <sanguis/client/exp_for_next_level.hpp>
#include <sanguis/client/health.hpp>
#include <sanguis/client/level.hpp>
#include <sanguis/client/max_health.hpp>
#include <sanguis/gui/context.hpp>
#include <sanguis/gui/fixed_area.hpp>
#include <sanguis/gui/master.hpp>
#include <sanguis/gui/widget/bar.hpp>
#include <sanguis/gui/widget/box_container.hpp>
#include <sanguis/gui/widget/text.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/input/cursor/object_fwd.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/timer/frames_counter.hpp>
#include <fcppt/noncopyable.hpp>


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

class object
{
	FCPPT_NONCOPYABLE(
		object
	);
public:
	object(
		sge::font::object &,
		sge::renderer::device::ffp &,
		sge::input::keyboard::device &,
		sge::input::cursor::object &
	);

	~object();

	void
	health(
		sanguis::client::health
	);

	void
	max_health(
		sanguis::client::max_health
	);

	void
	experience(
		sanguis::client::exp
	);

	void
	level(
		sanguis::client::level,
		sanguis::client::exp_for_next_level
	);

	void
	add_weapon(
		sanguis::weapon_description const &
	);

	void
	remove_weapon(
		sanguis::is_primary_weapon
	);

	void
	update(
		sanguis::duration const &
	);

	void
	draw(
		sge::renderer::context::ffp &
	);
private:
	void
	update_exp();

	sanguis::optional_weapon_description &
	weapon_description(
		sanguis::is_primary_weapon
	);

	sanguis::client::exp exp_;

	sanguis::client::exp_for_next_level previous_exp_level_;

	sanguis::client::exp_for_next_level exp_for_next_level_;

	sge::timer::frames_counter frames_counter_;

	sanguis::optional_weapon_description primary_weapon_;

	sanguis::optional_weapon_description secondary_weapon_;

	sanguis::gui::context gui_context_;

			sanguis::gui::widget::text player_name_text_;

			sanguis::gui::widget::text level_text_;

		sanguis::gui::widget::box_container top_container_;

		sanguis::gui::widget::bar exp_bar_;

		sanguis::gui::widget::bar health_bar_;

	sanguis::gui::widget::box_container main_widget_;

	sanguis::gui::master gui_master_;

	sanguis::gui::fixed_area gui_area_;
};

}
}
}
}
}

#endif
