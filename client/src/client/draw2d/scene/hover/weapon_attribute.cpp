#include <sanguis/weapon_attribute.hpp>
#include <sanguis/weapon_attribute_value.hpp>
#include <sanguis/client/draw2d/scene/hover/weapon_attribute.hpp>
#include <sanguis/client/draw2d/scene/hover/weapon_attribute_diff.hpp>
#include <sanguis/client/gui/default_text_color.hpp>
#include <sanguis/client/gui/hud/weapon_attribute_color.hpp>
#include <sanguis/client/gui/hud/weapon_attribute_diff_to_string.hpp>
#include <sanguis/client/gui/hud/weapon_attribute_name.hpp>
#include <sanguis/client/gui/hud/weapon_attribute_text.hpp>
#include <sge/font/lit.hpp>
#include <sge/font/object_ref.hpp>
#include <sge/font/string.hpp>
#include <sge/gui/context_ref.hpp>
#include <sge/gui/text_color.hpp>
#include <sge/gui/style/const_reference.hpp>
#include <sge/gui/widget/base_fwd.hpp>
#include <sge/gui/widget/reference.hpp>
#include <sge/gui/widget/reference_alignment_pair.hpp>
#include <sge/gui/widget/reference_alignment_vector.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/renderer/device/ffp_ref.hpp>
#include <sge/rucksack/alignment.hpp>
#include <sge/rucksack/axis.hpp>
#include <fcppt/optional/maybe.hpp>


sanguis::client::draw2d::scene::hover::weapon_attribute::weapon_attribute(
	sge::gui::context_ref const _gui_context,
	sge::gui::style::const_reference const _gui_style,
	sge::renderer::device::ffp_ref const _renderer,
	sge::font::object_ref const _font,
	sanguis::weapon_attribute const &_attribute,
	sanguis::client::draw2d::scene::hover::weapon_attribute_diff const _attribute_diff
)
:
	name_{
		_gui_style,
		_renderer,
		_font,
		sanguis::client::gui::hud::weapon_attribute_name(
			_attribute.type()
		)
		+
		SGE_FONT_LIT(": "),
		sge::gui::text_color(
			sanguis::client::gui::hud::weapon_attribute_color()
		)
	},
	expander1_{
		sge::rucksack::axis::x
	},
	value_{
		_gui_style,
		_renderer,
		_font,
		sanguis::client::gui::hud::weapon_attribute_text(
			_attribute
		),
		sanguis::client::gui::default_text_color()
	},
	expander2_{
		sge::rucksack::axis::x
	},
	diff_{
		_gui_style,
		_renderer,
		_font,
		fcppt::optional::maybe(
			_attribute_diff.get(),
			[]{
				return
					sge::font::string();
			},
			[](
				sanguis::weapon_attribute_value const _diff
			)
			{
				return
					sanguis::client::gui::hud::weapon_attribute_diff_to_string(
						_diff
					);
			}
		),
		fcppt::optional::maybe(
			_attribute_diff.get(),
			[]{
				return
					sanguis::client::gui::default_text_color();
			},
			[](
				sanguis::weapon_attribute_value const _diff
			)
			{
				return
					_diff
					>
					0
					?
						sge::gui::text_color(
							sge::image::color::any::object{
								sge::image::color::predef::lightblue()
							}
						)
					:
						sge::gui::text_color(
							sge::image::color::any::object{
								sge::image::color::predef::red()
							}
						)
					;
			}
		)
	},
	container_{
		_gui_context,
		sge::gui::widget::reference_alignment_vector{
			sge::gui::widget::reference_alignment_pair{
				sge::gui::widget::reference{
					name_
				},
				sge::rucksack::alignment::center
			},
			sge::gui::widget::reference_alignment_pair{
				sge::gui::widget::reference{
					expander1_
				},
				sge::rucksack::alignment::center
			},
			sge::gui::widget::reference_alignment_pair{
				sge::gui::widget::reference{
					value_
				},
				sge::rucksack::alignment::center
			},
			sge::gui::widget::reference_alignment_pair{
				sge::gui::widget::reference{
					expander2_
				},
				sge::rucksack::alignment::center
			},
			sge::gui::widget::reference_alignment_pair{
				sge::gui::widget::reference{
					diff_
				},
				sge::rucksack::alignment::center
			}
		},
		sge::rucksack::axis::x
	}
{
}

sanguis::client::draw2d::scene::hover::weapon_attribute::~weapon_attribute()
= default;

sge::gui::widget::base &
sanguis::client::draw2d::scene::hover::weapon_attribute::widget()
{
	return
		container_;
}
