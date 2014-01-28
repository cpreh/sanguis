#include <sanguis/duration.hpp>
#include <sanguis/weapon_description.hpp>
#include <sanguis/client/to_gui_duration.hpp>
#include <sanguis/client/draw2d/scene/hud/weapon_attribute_color.hpp>
#include <sanguis/client/draw2d/scene/hud/weapon_attribute_text.hpp>
#include <sanguis/client/draw2d/scene/hud/weapon_name.hpp>
#include <sanguis/client/draw2d/scene/hud/weapon_tooltip.hpp>
#include <sanguis/gui/default_aspect.hpp>
#include <sanguis/gui/text_color.hpp>
#include <sanguis/gui/widget/box_container.hpp>
#include <sanguis/gui/widget/reference.hpp>
#include <sanguis/gui/widget/reference_alignment_pair.hpp>
#include <sanguis/gui/widget/reference_alignment_vector.hpp>
#include <sanguis/gui/widget/text.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/input/cursor/object_fwd.hpp>
#include <sge/input/keyboard/device_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/rucksack/alignment.hpp>
#include <sge/rucksack/axis.hpp>
#include <sge/rucksack/vector.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/algorithm/join.hpp>
#include <fcppt/algorithm/map.hpp>


sanguis::client::draw2d::scene::hud::weapon_tooltip::weapon_tooltip(
	sge::renderer::device::ffp &_renderer,
	sge::font::object &_font,
	sge::input::keyboard::device &_keyboard,
	sge::input::cursor::object &_cursor,
	sanguis::weapon_description const &_description
)
:
	gui_context_(),
	name_text_(
		_renderer,
		_font,
		sanguis::client::draw2d::scene::hud::weapon_name(
			_description.weapon_type()
		),
		sanguis::gui::text_color(
			sge::image::color::predef::black()
		)
	),
	attribute_texts_(
		fcppt::algorithm::map<
			text_unique_ptr_vector
		>(
			_description.attributes(),
			[
				&_renderer,
				&_font
			](
				sanguis::weapon_attribute const &_attribute
			)
			{
				return
					fcppt::make_unique_ptr<
						sanguis::gui::widget::text
					>(
						_renderer,
						_font,
						sanguis::client::draw2d::scene::hud::weapon_attribute_text(
							_attribute
						),
						sanguis::gui::text_color(
							sanguis::client::draw2d::scene::hud::weapon_attribute_color(
								_attribute.type()
							)
						)
					);
			}
		)
	),
	container_(
		gui_context_,
		fcppt::algorithm::join(
			sanguis::gui::widget::reference_alignment_vector{
				sanguis::gui::widget::reference_alignment_pair(
					sanguis::gui::widget::reference(
						name_text_
					),
					sge::rucksack::alignment::left_or_top
				)
			},
			fcppt::algorithm::map<
				sanguis::gui::widget::reference_alignment_vector
			>(
				attribute_texts_,
				[](
					text_unique_ptr const &_text
				)
				{
					return
						sanguis::gui::widget::reference_alignment_pair(
							sanguis::gui::widget::reference(
								*_text
							),
							sge::rucksack::alignment::left_or_top
						);
				}
			)
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
		// TODO!
		sge::rucksack::vector(
			300,
			200
		)
	)
{
}

sanguis::client::draw2d::scene::hud::weapon_tooltip::~weapon_tooltip()
{
}

void
sanguis::client::draw2d::scene::hud::weapon_tooltip::update(
	sanguis::duration const &_duration
)
{
	gui_master_.update(
		sanguis::client::to_gui_duration(
			_duration
		)
	);
}

void
sanguis::client::draw2d::scene::hud::weapon_tooltip::draw(
	sge::renderer::context::ffp &_render_context
)
{
	gui_master_.draw(
		_render_context
	);
}
