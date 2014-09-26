#include <sanguis/weapon_attribute_fwd.hpp>
#include <sanguis/client/weapon_pair_fwd.hpp>
#include <sanguis/client/draw2d/entities/hover/weapon.hpp>
#include <sanguis/client/draw2d/scene/hover/base.hpp>
#include <sanguis/client/draw2d/scene/hover/compare_weapons.hpp>
#include <sanguis/client/draw2d/scene/hover/weapon.hpp>
#include <sanguis/client/draw2d/scene/hover/weapon_attribute.hpp>
#include <sanguis/client/draw2d/scene/hover/weapon_attribute_unique_ptr.hpp>
#include <sanguis/client/draw2d/sprite/center.hpp>
#include <sanguis/client/load/hud/context.hpp>
#include <sanguis/gui/draw.hpp>
#include <sanguis/gui/style/base_fwd.hpp>
#include <sanguis/gui/widget/reference.hpp>
#include <sanguis/gui/widget/reference_alignment_pair.hpp>
#include <sanguis/gui/widget/reference_alignment_vector.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/rucksack/alignment.hpp>
#include <sge/rucksack/axis.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/algorithm/join.hpp>
#include <fcppt/algorithm/map.hpp>


sanguis::client::draw2d::scene::hover::weapon::weapon(
	sanguis::gui::style::base const &_gui_style,
	sanguis::gui::renderer::base &_gui_renderer,
	sge::renderer::device::ffp &_renderer,
	sge::font::object &_font,
	sanguis::client::draw2d::sprite::center const _center,
	sanguis::client::load::hud::context &_hud_resources,
	sanguis::client::weapon_pair const &_player_weapons,
	sanguis::client::draw2d::entities::hover::weapon const &_info
)
:
	gui_renderer_(
		_gui_renderer
	),
	gui_context_(),
	image_(
		_gui_style,
		_hud_resources.weapon_icon(
			_info.get().weapon_type()
		)
	),
	weapon_attributes_(
		fcppt::algorithm::map<
			sanguis::client::draw2d::scene::hover::weapon::weapon_attribute_vector
		>(
			_info.get().attributes(),
			[
				this,
				&_info,
				&_gui_style,
				&_renderer,
				&_font,
				&_player_weapons
			](
				sanguis::weapon_attribute const &_attribute
			)
			{
				return
					fcppt::make_unique_ptr<
						sanguis::client::draw2d::scene::hover::weapon_attribute
					>(
						gui_context_,
						_gui_style,
						_renderer,
						_font,
						_attribute,
						sanguis::client::draw2d::scene::hover::compare_weapons(
							_info.get().weapon_type(),
							_attribute,
							_player_weapons
						)
					);
			}
		)
	),
	container_(
		gui_context_,
		fcppt::algorithm::join(
			sanguis::gui::widget::reference_alignment_vector{
				sanguis::gui::widget::reference_alignment_pair{
					sanguis::gui::widget::reference{
						image_
					},
					sge::rucksack::alignment::center
				}
			},
			fcppt::algorithm::map<
				sanguis::gui::widget::reference_alignment_vector
			>(
				weapon_attributes_,
				[](
					sanguis::client::draw2d::scene::hover::weapon_attribute_unique_ptr const &_attribute
				)
				{
					return
						sanguis::gui::widget::reference_alignment_pair{
							sanguis::gui::widget::reference{
								_attribute->widget()
							},
							sge::rucksack::alignment::left_or_top
						};
				}
			)
		),
		sge::rucksack::axis::y
	),
	gui_area_(
		container_,
		_center.get()
	),
	gui_background_(
		gui_area_
	)
{
}

sanguis::client::draw2d::scene::hover::weapon::~weapon()
{
}

void
sanguis::client::draw2d::scene::hover::weapon::draw(
	sge::renderer::context::ffp &_render_context
)
{
	sanguis::gui::draw(
		gui_renderer_,
		_render_context,
		gui_background_,
		gui_area_
	);
}
