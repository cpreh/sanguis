#ifndef SANGUIS_CLIENT_GUI_HUD_OBJECT_HPP_INCLUDED
#define SANGUIS_CLIENT_GUI_HUD_OBJECT_HPP_INCLUDED

#include <sanguis/diff_clock.hpp>
#include <sanguis/duration.hpp>
#include <sanguis/is_primary_weapon.hpp>
#include <sanguis/magazine_remaining.hpp>
#include <sanguis/player_name_fwd.hpp>
#include <sanguis/weapon_description_fwd.hpp>
#include <sanguis/world_name_fwd.hpp>
#include <sanguis/client/exp.hpp>
#include <sanguis/client/exp_for_next_level.hpp>
#include <sanguis/client/level.hpp>
#include <sanguis/client/optional_health_pair_fwd.hpp>
#include <sanguis/client/slowed_duration_fwd.hpp>
#include <sanguis/client/gui/hud/object_fwd.hpp>
#include <sanguis/client/gui/hud/weapon_details_fwd.hpp>
#include <sanguis/client/gui/hud/weapon_widget.hpp>
#include <sanguis/client/load/hud/context_fwd.hpp>
#include <sanguis/gui/context.hpp>
#include <sanguis/gui/master.hpp>
#include <sanguis/gui/background/none.hpp>
#include <sanguis/gui/main_area/screen_corner.hpp>
#include <sanguis/gui/style/base_fwd.hpp>
#include <sanguis/gui/widget/bar.hpp>
#include <sanguis/gui/widget/box_container.hpp>
#include <sanguis/gui/widget/expander.hpp>
#include <sanguis/gui/widget/frame.hpp>
#include <sanguis/gui/widget/preferred_size.hpp>
#include <sanguis/gui/widget/text.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/input/cursor/object_fwd.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/rucksack/rect_fwd.hpp>
#include <sge/timer/frames_counter.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/optional_decl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <memory>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace client
{
namespace gui
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
		sanguis::client::load::hud::context &,
		sanguis::gui::style::base const &,
		sge::font::object &,
		sge::renderer::device::ffp &,
		sge::viewport::manager &,
		sge::input::keyboard::device &,
		sge::input::cursor::object &
	);

	~object();

	void
	health_pair(
		sanguis::client::optional_health_pair const &
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
	magazine_remaining(
		sanguis::is_primary_weapon,
		sanguis::magazine_remaining
	);

	void
	reload_time(
		sanguis::is_primary_weapon,
		sanguis::duration
	);

	void
	world_name(
		sanguis::world_name const &
	);

	void
	player_name(
		sanguis::player_name const &
	);

	void
	update(
		sanguis::duration
	);

	void
	update_server(
		sanguis::client::slowed_duration
	);

	void
	pause(
		bool
	);

	void
	draw(
		sge::renderer::context::ffp &
	);

	void
	details(
		bool
	);
private:
	typedef
	std::unique_ptr<
		sanguis::client::gui::hud::weapon_widget
	>
	weapon_widget_unique_ptr;

	typedef
	fcppt::optional<
		weapon_widget_unique_ptr
	>
	optional_weapon_widget_unique_ptr;

	optional_weapon_widget_unique_ptr &
	weapon_widget(
		sanguis::is_primary_weapon
	);

	sanguis::client::gui::hud::weapon_widget &
	weapon_widget_checked(
		sanguis::is_primary_weapon
	);

	template<
		typename Function
	>
	void
	update_weapon_widgets(
		Function const &
	);

	template<
		typename Function
	>
	void
	foreach_weapon(
		Function const &
	);

	void
	update_exp();

	void
	create_details();

	void
	destroy_details();

	sanguis::diff_clock reload_clock_;

	sanguis::client::load::hud::context &resources_;

	sanguis::gui::style::base const &gui_style_;

	sge::font::object &font_;

	sge::renderer::device::ffp &renderer_;

	sanguis::client::exp exp_;

	sanguis::client::exp_for_next_level previous_exp_level_;

	sanguis::client::exp_for_next_level exp_for_next_level_;

	sge::timer::frames_counter frames_counter_;

	sanguis::gui::context gui_context_;

				sanguis::gui::widget::text world_name_text_;

					sanguis::gui::widget::text player_name_text_;

					sanguis::gui::widget::expander name_level_gap_;

					sanguis::gui::widget::text level_text_;

				sanguis::gui::widget::box_container text_container_;

				sanguis::gui::widget::bar exp_bar_;

				sanguis::gui::widget::bar health_bar_;

			sanguis::gui::widget::box_container middle_container_;

		sanguis::gui::widget::frame middle_frame_;

					sanguis::gui::widget::preferred_size primary_dummy_widget_h_;

					optional_weapon_widget_unique_ptr primary_weapon_;

				sanguis::gui::widget::box_container primary_weapon_container_inner_;

				sanguis::gui::widget::preferred_size primary_dummy_widget_w_;

			sanguis::gui::widget::box_container primary_weapon_container_;

		sanguis::gui::widget::frame primary_weapon_frame_;

					sanguis::gui::widget::preferred_size secondary_dummy_widget_h_;

					optional_weapon_widget_unique_ptr secondary_weapon_;

				sanguis::gui::widget::box_container secondary_weapon_container_inner_;

				sanguis::gui::widget::preferred_size secondary_dummy_widget_w_;

			sanguis::gui::widget::box_container secondary_weapon_container_;

		sanguis::gui::widget::frame secondary_weapon_frame_;

	sanguis::gui::widget::box_container main_widget_;

	sanguis::gui::main_area::screen_corner gui_area_;

	sanguis::gui::master gui_master_;

	sanguis::gui::background::none gui_background_;

	typedef
	std::unique_ptr<
		sanguis::client::gui::hud::weapon_details
	>
	weapon_details_unique_ptr;

	weapon_details_unique_ptr weapon_details_;

	bool paused_;
};

}
}
}
}

#endif
