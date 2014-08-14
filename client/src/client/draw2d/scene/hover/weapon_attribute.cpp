#include <sanguis/weapon_attribute.hpp>
#include <sanguis/client/draw2d/scene/hover/weapon_attribute.hpp>
#include <sanguis/client/gui/default_text_color.hpp>
#include <sanguis/client/gui/hud/weapon_attribute_color.hpp>
#include <sanguis/client/gui/hud/weapon_attribute_name.hpp>
#include <sanguis/client/gui/hud/weapon_attribute_value_to_string.hpp>
#include <sanguis/gui/context_fwd.hpp>
#include <sanguis/gui/default_aspect.hpp>
#include <sanguis/gui/style/base_fwd.hpp>
#include <sanguis/gui/widget/base_fwd.hpp>
#include <sanguis/gui/widget/reference.hpp>
#include <sanguis/gui/widget/reference_alignment_pair.hpp>
#include <sanguis/gui/widget/reference_alignment_vector.hpp>
#include <sge/font/lit.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/rucksack/alignment.hpp>
#include <sge/rucksack/axis.hpp>


sanguis::client::draw2d::scene::hover::weapon_attribute::weapon_attribute(
	sanguis::gui::context &_gui_context,
	sanguis::gui::style::base const &_gui_style,
	sge::renderer::device::ffp &_renderer,
	sge::font::object &_font,
	sanguis::weapon_attribute const &_attribute
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
		sanguis::gui::text_color(
			sanguis::client::gui::hud::weapon_attribute_color(
				_attribute.type()
			)
		)
	},
	expander1_{
		sge::rucksack::axis::x
	},
	value_{
		_gui_style,
		_renderer,
		_font,
		sanguis::client::gui::hud::weapon_attribute_value_to_string(
			// TODO
			_attribute.extra().get()
			?
			(
				_attribute.base().get()
				+
				*_attribute.extra().get()
			)
			:
				_attribute.base().get()
		),
		sanguis::client::gui::default_text_color()
	},
	diff_{
		_gui_style,
		_renderer,
		_font,
		// TODO:
		sge::font::string(),
		sanguis::client::gui::default_text_color()
	},
	container_{
		_gui_context,
		sanguis::gui::widget::reference_alignment_vector{
			sanguis::gui::widget::reference_alignment_pair{
				sanguis::gui::widget::reference{
					name_
				},
				sge::rucksack::alignment::center
			},
			sanguis::gui::widget::reference_alignment_pair{
				sanguis::gui::widget::reference{
					expander1_
				},
				sge::rucksack::alignment::center
			},
			sanguis::gui::widget::reference_alignment_pair{
				sanguis::gui::widget::reference{
					value_
				},
				sge::rucksack::alignment::center
			},
			sanguis::gui::widget::reference_alignment_pair{
				sanguis::gui::widget::reference{
					diff_
				},
				sge::rucksack::alignment::center
			}
		},
		sge::rucksack::axis::x,
		sanguis::gui::default_aspect()
	}
{
}

sanguis::client::draw2d::scene::hover::weapon_attribute::~weapon_attribute()
{
}

sanguis::gui::widget::base &
sanguis::client::draw2d::scene::hover::weapon_attribute::widget()
{
	return
		container_;
}
