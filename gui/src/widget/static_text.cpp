#include <sanguis/gui/default_aspect.hpp>
#include <sanguis/gui/style/base.hpp>
#include <sanguis/gui/widget/base.hpp>
#include <sanguis/gui/widget/static_text.hpp>
#include <sge/font/metrics.hpp>
#include <sge/font/object.hpp>
#include <sge/font/rect.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text_parameters.hpp>
#include <sge/font/vector.hpp>
#include <sge/font/align_h/left.hpp>
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
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/vector/structure_cast.hpp>


sanguis::gui::widget::static_text::static_text(
	sanguis::gui::style::base const &_style,
	sge::renderer::device::ffp &_renderer,
	sge::font::object &_font,
	sge::font::string const &_value,
	sanguis::gui::text_color const &_text_color
)
:
	sanguis::gui::widget::base(),
	style_(
		_style
	),
	renderer_(
		_renderer
	),
	static_text_(
		_renderer,
		_font,
		_value,
		sge::font::text_parameters(
			sge::font::align_h::left()
		),
		sge::font::vector::null(),
		_text_color.get(),
		sge::renderer::texture::emulate_srgb::no
	),
	layout_(
		sge::rucksack::axis_policy2(
			// TODO: Make this easier to initialize
			sge::rucksack::axis_policy(
				sge::rucksack::minimum_size(
					static_text_.logical_size().w()
					+
					style_.text_spacing().w()
				),
				sge::rucksack::preferred_size(
					sge::rucksack::optional_scalar(
						static_text_.logical_size().w()
						+
						style_.text_spacing().w()
					)
				),
				sge::rucksack::is_expanding(
					false
				)
			),
			sge::rucksack::axis_policy(
				sge::rucksack::minimum_size(
					_font.metrics().height().get()
					+
					style_.text_spacing().h()
				),
				sge::rucksack::preferred_size(
					sge::rucksack::optional_scalar(
						_font.metrics().height().get()
						+
						style_.text_spacing().h()
					)
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

sanguis::gui::widget::static_text::~static_text()
{
}

sge::rucksack::widget::base &
sanguis::gui::widget::static_text::layout()
{
	return
		layout_;
}

void
sanguis::gui::widget::static_text::on_draw(
	sge::renderer::context::ffp &_context
)
{
	style_.draw_text(
		renderer_,
		_context,
		this->layout().area()
	);

	static_text_.pos(
		fcppt::math::vector::structure_cast<
			sge::font::vector
		>(
			this->layout().position()
			+
			style_.text_spacing()
			/
			2
		)
	);

	static_text_.draw(
		_context
	);
}
