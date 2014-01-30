#include <sanguis/duration.hpp>
#include <sanguis/optional_weapon_description.hpp>
#include <sanguis/client/gui/to_duration.hpp>
#include <sanguis/client/gui/hud/weapon_details.hpp>
#include <sanguis/client/gui/hud/weapon_tooltip.hpp>
#include <sanguis/client/gui/hud/weapon_tooltip_unique_ptr.hpp>
#include <sanguis/gui/default_aspect.hpp>
#include <sanguis/gui/widget/reference.hpp>
#include <sanguis/gui/widget/reference_alignment_pair.hpp>
#include <sanguis/gui/widget/reference_alignment_vector.hpp>
#include <sanguis/load/hud/context_fwd.hpp>
#include <sge/input/cursor/object_fwd.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/rucksack/alignment.hpp>
#include <sge/rucksack/axis.hpp>
#include <sge/rucksack/dim.hpp>
#include <sge/rucksack/rect.hpp>
#include <sge/rucksack/vector.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/algorithm/fold.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <vector>
#include <fcppt/config/external_end.hpp>


sanguis::client::gui::hud::weapon_details::weapon_details(
	sanguis::load::hud::context &_resources,
	sge::renderer::device::ffp &_renderer,
	sge::font::object &_font,
	sge::input::keyboard::device &_keyboard,
	sge::input::cursor::object &_cursor,
	sanguis::optional_weapon_description const &_weapon1,
	sanguis::optional_weapon_description const &_weapon2,
	sge::rucksack::rect const _hud_area
)
:
	gui_context_(),
	tooltips_(
		fcppt::algorithm::fold(
			std::vector<
				sanguis::optional_weapon_description
			>{
				_weapon1,
				_weapon2
			},
			tooltip_vector(),
			[
				this,
				&_renderer,
				&_font
			](
				sanguis::optional_weapon_description const &_desc,
				tooltip_vector &&_state
			)
			{
				if(
					_desc
				)
					_state.push_back(
						fcppt::make_unique_ptr<
							sanguis::client::gui::hud::weapon_tooltip
						>(
							gui_context_,
							_renderer,
							_font,
							*_desc
						)
					);

				return
					std::move(
						_state
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
	gui_master_(
		_renderer,
		_keyboard,
		_cursor,
		gui_context_,
		container_
	),
	gui_area_(
		container_,
		sge::rucksack::vector(
			0,
			_hud_area.bottom()
		)
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
		_render_context
	);
}
