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
#include <sanguis/client/load/hud/context_ref.hpp>
#include <sge/font/object_ref.hpp>
#include <sge/gui/draw.hpp>
#include <sge/gui/main_area/base.hpp>
#include <sge/gui/renderer/base_ref.hpp>
#include <sge/gui/style/const_reference.hpp>
#include <sge/gui/widget/base.hpp>
#include <sge/gui/widget/reference.hpp>
#include <sge/gui/widget/reference_alignment_pair.hpp>
#include <sge/gui/widget/reference_alignment_vector.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <sge/rucksack/alignment.hpp>
#include <sge/rucksack/axis.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/reference_to_base.hpp>
#include <fcppt/algorithm/map.hpp>
#include <fcppt/container/join.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sanguis::client::draw2d::scene::hover::weapon::weapon(
	sge::gui::style::const_reference const _gui_style,
	sge::gui::renderer::base_ref const _gui_renderer,
	sge::renderer::device::ffp_ref const _renderer,
	sge::font::object_ref const _font,
	sanguis::client::draw2d::sprite::center const &_center,
	sanguis::client::load::hud::context_ref const _hud_resources,
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
		fcppt::make_cref(
			_hud_resources->weapon_icon(
				_info.get().weapon_type()
			)
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
						fcppt::make_ref(
							gui_context_
						),
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
		fcppt::make_ref(
			gui_context_
		),
		fcppt::container::join(
			sge::gui::widget::reference_alignment_vector{
				sge::gui::widget::reference_alignment_pair{
					sge::gui::widget::reference{
						image_
					},
					sge::rucksack::alignment::center
				}
			},
			fcppt::algorithm::map<
				sge::gui::widget::reference_alignment_vector
			>(
				weapon_attributes_,
				[](
					sanguis::client::draw2d::scene::hover::weapon_attribute_unique_ptr const &_attribute
				)
				{
					return
						sge::gui::widget::reference_alignment_pair{
							sge::gui::widget::reference{
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
		fcppt::reference_to_base<
			sge::gui::widget::base
		>(
			fcppt::make_ref(
				container_
			)
		),
		_center.get()
	),
	gui_background_(
		fcppt::reference_to_base<
			sge::gui::main_area::base
		>(
			fcppt::make_ref(
				gui_area_
			)
		)
	)
{
}

FCPPT_PP_POP_WARNING

sanguis::client::draw2d::scene::hover::weapon::~weapon()
= default;

void
sanguis::client::draw2d::scene::hover::weapon::draw(
	sge::renderer::context::ffp &_render_context
)
{
	sge::gui::draw(
		gui_renderer_.get(),
		_render_context,
		gui_background_,
		gui_area_
	);
}
