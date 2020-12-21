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
#include <sanguis/client/load/hud/context_ref.hpp>
#include <sge/font/object_ref.hpp>
#include <sge/gui/context.hpp>
#include <sge/gui/master.hpp>
#include <sge/gui/background/none.hpp>
#include <sge/gui/main_area/screen_corner.hpp>
#include <sge/gui/style/const_reference.hpp>
#include <sge/gui/widget/bar.hpp>
#include <sge/gui/widget/box_container.hpp>
#include <sge/gui/widget/expander.hpp>
#include <sge/gui/widget/frame.hpp>
#include <sge/gui/widget/preferred_size.hpp>
#include <sge/gui/widget/text.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <sge/rucksack/rect_fwd.hpp>
#include <sge/timer/frames_counter.hpp>
#include <sge/viewport/manager_ref.hpp>
#include <fcppt/nonmovable.hpp>
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/optional/object_decl.hpp>


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
	FCPPT_NONMOVABLE(
		object
	);
public:
	object(
		sanguis::client::load::hud::context_ref,
		sge::gui::style::const_reference,
		sge::font::object_ref,
		sge::renderer::device::ffp_ref,
		sge::viewport::manager_ref
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
		sge::renderer::context::ffp & // NOLINT(google-runtime-references)
	); // NOLINT(google-runtime-references)

	void
	details(
		bool
	);
private:
	using
	weapon_widget_unique_ptr
	=
	fcppt::unique_ptr<
		sanguis::client::gui::hud::weapon_widget
	>;

	using
	optional_weapon_widget_unique_ptr
	=
	fcppt::optional::object<
		weapon_widget_unique_ptr
	>;

	[[nodiscard]]
	optional_weapon_widget_unique_ptr &
	weapon_widget(
		sanguis::is_primary_weapon
	);

	[[nodiscard]]
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

	sanguis::client::load::hud::context_ref const resources_;

	sge::gui::style::const_reference const gui_style_;

	sge::font::object_ref const font_;

	sge::renderer::device::ffp_ref const renderer_;

	sanguis::client::exp exp_;

	sanguis::client::exp_for_next_level previous_exp_level_;

	sanguis::client::exp_for_next_level exp_for_next_level_;

	sge::timer::frames_counter frames_counter_;

	sge::gui::context gui_context_;

				sge::gui::widget::text world_name_text_;

					sge::gui::widget::text player_name_text_;

					sge::gui::widget::expander name_level_gap_;

					sge::gui::widget::text level_text_;

				sge::gui::widget::box_container text_container_;

				sge::gui::widget::bar exp_bar_;

				sge::gui::widget::bar health_bar_;

			sge::gui::widget::box_container middle_container_;

		sge::gui::widget::frame middle_frame_;

					sge::gui::widget::preferred_size primary_dummy_widget_h_;

					optional_weapon_widget_unique_ptr primary_weapon_;

				sge::gui::widget::box_container primary_weapon_container_inner_;

				sge::gui::widget::preferred_size primary_dummy_widget_w_;

			sge::gui::widget::box_container primary_weapon_container_;

		sge::gui::widget::frame primary_weapon_frame_;

					sge::gui::widget::preferred_size secondary_dummy_widget_h_;

					optional_weapon_widget_unique_ptr secondary_weapon_;

				sge::gui::widget::box_container secondary_weapon_container_inner_;

				sge::gui::widget::preferred_size secondary_dummy_widget_w_;

			sge::gui::widget::box_container secondary_weapon_container_;

		sge::gui::widget::frame secondary_weapon_frame_;

	sge::gui::widget::box_container main_widget_;

	sge::gui::main_area::screen_corner gui_area_;

	sge::gui::master gui_master_;

	sge::gui::background::none gui_background_;

	using
	weapon_details_unique_ptr
	=
	fcppt::unique_ptr<
		sanguis::client::gui::hud::weapon_details
	>;

	using
	optional_weapon_details_unique_ptr
	=
	fcppt::optional::object<
		weapon_details_unique_ptr
	>;

	optional_weapon_details_unique_ptr weapon_details_;

	bool paused_;
};

}
}
}
}

#endif
