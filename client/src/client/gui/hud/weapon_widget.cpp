#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/duration.hpp>
#include <sanguis/duration_second.hpp>
#include <sanguis/magazine_remaining.hpp>
#include <sanguis/weapon_description.hpp>
#include <sanguis/client/gui/default_text_color.hpp>
#include <sanguis/client/gui/hud/weapon_widget.hpp>
#include <sanguis/client/gui/style/text_color.hpp>
#include <sanguis/client/load/hud/context.hpp>
#include <sge/font/lit.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/gui/context_fwd.hpp>
#include <sge/gui/fill_color.hpp>
#include <sge/gui/fill_level.hpp>
#include <sge/gui/optional_needed_width.hpp>
#include <sge/gui/text_color.hpp>
#include <sge/gui/style/base_fwd.hpp>
#include <sge/gui/widget/box_container.hpp>
#include <sge/gui/widget/image.hpp>
#include <sge/gui/widget/reference.hpp>
#include <sge/gui/widget/reference_alignment_pair.hpp>
#include <sge/gui/widget/reference_alignment_vector.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/rucksack/alignment.hpp>
#include <sge/rucksack/axis.hpp>
#include <sge/rucksack/dim.hpp>
#include <sge/timer/elapsed_fractional.hpp>
#include <fcppt/output_to_string.hpp>
#include <fcppt/strong_typedef_output.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sanguis::client::gui::hud::weapon_widget::weapon_widget(
	sanguis::diff_clock const &_diff_clock,
	sanguis::client::load::hud::context &_resources,
	sge::gui::context &_gui_context,
	sge::gui::style::base const &_gui_style,
	sge::renderer::device::ffp &_renderer,
	sge::font::object &_font,
	sanguis::weapon_description const &_description
)
:
	description_(
		_description
	),
	reload_time_(
		sanguis::diff_timer::parameters(
			_diff_clock,
			sanguis::duration_second(
				// TODO: What should we choose here?
				1
			)
		)
		.expired(
			true
		)
	),
	image_(
		_gui_style,
		_resources.weapon_icon(
			_description.weapon_type()
		)
	),
	text_(
		_gui_style,
		_renderer,
		_font,
		this->make_text(
			_description.magazine_remaining()
		),
		sanguis::client::gui::default_text_color(),
		sge::gui::optional_needed_width()
	),
	cooldown_bar_{
		_gui_style,
		sge::rucksack::dim{
			10,
			50 // TODO: Should this be expanding?
		},
		sge::rucksack::axis::y,
		sge::gui::fill_color{
			sanguis::client::gui::style::text_color()
		},
		sge::gui::fill_level{
			1.f
		}
	},
	container_(
		_gui_context,
		sge::gui::widget::reference_alignment_vector{
			sge::gui::widget::reference_alignment_pair(
				sge::gui::widget::reference(
					image_
				),
				sge::rucksack::alignment::center
			),
			sge::gui::widget::reference_alignment_pair(
				sge::gui::widget::reference(
					text_
				),
				sge::rucksack::alignment::center
			),
			sge::gui::widget::reference_alignment_pair(
				sge::gui::widget::reference(
					cooldown_bar_
				),
				sge::rucksack::alignment::center
			)
		},
		sge::rucksack::axis::x
	)
{
}

FCPPT_PP_POP_WARNING

sanguis::client::gui::hud::weapon_widget::~weapon_widget()
{
}

void
sanguis::client::gui::hud::weapon_widget::magazine_remaining(
	sanguis::magazine_remaining const _magazine_remaining
)
{
	text_.value(
		this->make_text(
			_magazine_remaining
		)
	);
}

void
sanguis::client::gui::hud::weapon_widget::reload_time(
	sanguis::duration const _reload_time
)
{
	reload_time_.interval(
		_reload_time
	);

	reload_time_.reset();
}

void
sanguis::client::gui::hud::weapon_widget::update()
{
	cooldown_bar_.value(
		sge::gui::fill_level(
			sge::timer::elapsed_fractional<
				sge::gui::fill_level::value_type
			>(
				reload_time_
			)
		)
	);
}

sge::gui::widget::box_container &
sanguis::client::gui::hud::weapon_widget::widget()
{
	return
		container_;
}

sanguis::weapon_description const &
sanguis::client::gui::hud::weapon_widget::weapon_description() const
{
	return
		description_;
}

sge::font::string
sanguis::client::gui::hud::weapon_widget::make_text(
	sanguis::magazine_remaining const _magazine_remaining
) const
{
	sge::font::string value(
		fcppt::output_to_string<
			sge::font::string
		>(
			_magazine_remaining
		)
	);

	if(
		description_.magazine_size().get()
		!=
		0u
	)
		value +=
			SGE_FONT_LIT('/')
			+
			fcppt::output_to_string<
				sge::font::string
			>(
				description_.magazine_size()
			);

	if(
		description_.magazine_extra().get()
		!=
		0u
	)
		value +=
			SGE_FONT_LIT('+')
			+
			fcppt::output_to_string<
				sge::font::string
			>(
				description_.magazine_extra()
			);

	return
		value;
}
