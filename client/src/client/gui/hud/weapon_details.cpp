#include <sanguis/duration.hpp>
#include <sanguis/optional_weapon_description.hpp>
#include <sanguis/client/gui/to_duration.hpp>
#include <sanguis/client/gui/hud/weapon_details.hpp>
#include <sanguis/client/gui/hud/weapon_tooltip.hpp>
#include <sanguis/client/gui/hud/weapon_tooltip_unique_ptr.hpp>
#include <sanguis/client/load/hud/context_fwd.hpp>
#include <sanguis/gui/default_aspect.hpp>
#include <sanguis/gui/gravity.hpp>
#include <sanguis/gui/widget/reference.hpp>
#include <sanguis/gui/widget/reference_alignment_pair.hpp>
#include <sanguis/gui/widget/reference_alignment_vector.hpp>
#include <sge/input/cursor/object_fwd.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp.hpp>
#include <sge/rucksack/alignment.hpp>
#include <sge/rucksack/axis.hpp>
#include <sge/rucksack/dim.hpp>
#include <sge/rucksack/vector.hpp>
#include <sge/viewport/manager_fwd.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional_bind_construct.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/algorithm/map_optional.hpp>
#include <fcppt/config/external_begin.hpp>
#include <array>
#include <fcppt/config/external_end.hpp>


sanguis::client::gui::hud::weapon_details::weapon_details(
	sanguis::client::load::hud::context &_resources,
	sge::renderer::device::ffp &_renderer,
	sge::viewport::manager &_viewport_manager,
	sge::font::object &_font,
	sge::input::keyboard::device &_keyboard,
	sge::input::cursor::object &_cursor,
	sanguis::optional_weapon_description const &_weapon1,
	sanguis::optional_weapon_description const &_weapon2
)
:
	gui_context_(),
	tooltips_(
		fcppt::algorithm::map_optional<
			tooltip_vector
		>(
			std::array<
				sanguis::optional_weapon_description,
				2
			>{{
				_weapon1,
				_weapon2
			}},
			[
				this,
				&_renderer,
				&_font
			](
				sanguis::optional_weapon_description const &_desc
			)
			{
				return
					fcppt::optional_bind_construct(
						_desc,
						[
							this,
							&_renderer,
							&_font
						](
							sanguis::weapon_description const &_ndesc
						)
						{
							return
								fcppt::make_unique_ptr<
									sanguis::client::gui::hud::weapon_tooltip
								>(
									gui_context_,
									_renderer,
									_font,
									_ndesc
								);
						}
					);
			}
		)
	),
	container_(
		gui_context_,
		fcppt::algorithm::map<
			sanguis::gui::widget::reference_alignment_vector
		>(
			tooltips_,
			[](
				sanguis::client::gui::hud::weapon_tooltip_unique_ptr const &_tooltip
			)
			{
				return
					sanguis::gui::widget::reference_alignment_pair(
						sanguis::gui::widget::reference(
							_tooltip->widget()
						),
						sge::rucksack::alignment::left_or_top
					);
			}
		),
		sge::rucksack::axis::y,
		sanguis::gui::default_aspect()
	),
	gui_area_(
		_renderer,
		_viewport_manager,
		gui_context_,
		container_,
		sanguis::gui::gravity::south_west
	),
	gui_master_(
		_keyboard,
		_cursor,
		gui_context_,
		gui_area_
	),
	gui_background_(
		_renderer,
		gui_area_
	)
{
}

sanguis::client::gui::hud::weapon_details::~weapon_details()
{
}

void
sanguis::client::gui::hud::weapon_details::update(
	sanguis::duration const &_duration
)
{
	gui_master_.update(
		sanguis::client::gui::to_duration(
			_duration
		)
	);
}

void
sanguis::client::gui::hud::weapon_details::draw(
	sge::renderer::context::ffp &_render_context
)
{
	gui_master_.draw(
		_render_context,
		gui_background_
	);
}
