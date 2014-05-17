#include <sanguis/gui/default_aspect.hpp>
#include <sanguis/gui/optional_needed_width.hpp>
#include <sanguis/gui/widget/base.hpp>
#include <sanguis/gui/widget/text.hpp>
#include <sge/font/metrics.hpp>
#include <sge/font/object.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text_parameters.hpp>
#include <sge/font/v_center.hpp>
#include <sge/font/vector.hpp>
#include <sge/font/align_h/center.hpp>
#include <sge/font/align_h/max_width.hpp>
#include <sge/font/draw/simple.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/rucksack/axis_policy.hpp>
#include <sge/rucksack/axis_policy2.hpp>
#include <sge/rucksack/is_expanding.hpp>
#include <sge/rucksack/minimum_size.hpp>
#include <sge/rucksack/optional_scalar.hpp>
#include <sge/rucksack/preferred_size.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <sge/rucksack/widget/dummy.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/structure_cast.hpp>


sanguis::gui::widget::text::text(
	sge::renderer::device::ffp &_renderer,
	sge::font::object &_font,
	sge::font::string const &_value,
	sanguis::gui::text_color const &_text_color,
	sanguis::gui::optional_needed_width const _needed_width
)
:
	sanguis::gui::widget::base(),
	renderer_(
		_renderer
	),
	font_(
		_font
	),
	text_color_(
		_text_color
	),
	value_(
		_value
	),
	layout_(
		sge::rucksack::axis_policy2(
			sge::rucksack::axis_policy(
				sge::rucksack::minimum_size(
					_needed_width
					?
						_needed_width->get()
					:
						0
				),
				sge::rucksack::preferred_size(
					sge::rucksack::optional_scalar()
				),
				sge::rucksack::is_expanding(
					!_needed_width.has_value()
				)
			),
			sge::rucksack::axis_policy(
				sge::rucksack::minimum_size(
					font_.metrics().height().get()
				),
				sge::rucksack::preferred_size(
					sge::rucksack::optional_scalar()
				),
				sge::rucksack::is_expanding(
					false
				)
			),
			sanguis::gui::default_aspect()
		)
	)
{
}

sanguis::gui::widget::text::~text()
{
}

void
sanguis::gui::widget::text::value(
	sge::font::string const &_value
)
{
	value_ =
		_value;
}

void
sanguis::gui::widget::text::text_color(
	sanguis::gui::text_color const &_text_color
)
{
	text_color_ =
		_text_color;
}

sge::rucksack::widget::base &
sanguis::gui::widget::text::layout()
{
	return
		layout_;
}

void
sanguis::gui::widget::text::on_draw(
	sge::renderer::context::ffp &_context
)
{
	sge::font::draw::simple(
		renderer_,
		_context,
		font_,
		value_,
		sge::font::text_parameters(
			sge::font::align_h::center(
				sge::font::align_h::max_width(
					layout_.size().w()
				)
			)
		),
		fcppt::math::vector::structure_cast<
			sge::font::vector
		>(
			layout_.position()
		)
		+
		sge::font::vector(
			0,
			sge::font::v_center(
				font_.metrics().height(),
				layout_.size().h()
			)
		),
		text_color_.get(),
		sge::renderer::texture::emulate_srgb::no
	);
}
