#include <sanguis/gui/default_aspect.hpp>
#include <sanguis/gui/aux_/style/text_color.hpp>
#include <sanguis/gui/widget/base.hpp>
#include <sanguis/gui/widget/text.hpp>
#include <sge/font/align_h.hpp>
#include <sge/font/metrics.hpp>
#include <sge/font/object.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text_parameters.hpp>
#include <sge/font/v_center.hpp>
#include <sge/font/vector.hpp>
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
	sge::font::string const &_value
)
:
	sanguis::gui::widget::base(),
	renderer_(
		_renderer
	),
	font_(
		_font
	),
	value_(
		_value
	),
	layout_(
		sge::rucksack::axis_policy2(
			sge::rucksack::axis_policy(
				sge::rucksack::minimum_size(
					0
				),
				sge::rucksack::preferred_size(
					sge::rucksack::optional_scalar()
				),
				sge::rucksack::is_expanding(
					true
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
			sge::font::align_h::left
		)
		.max_width(
			layout_.size().w()
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
		sanguis::gui::aux_::style::text_color(),
		sge::renderer::texture::emulate_srgb::no
	);
}
