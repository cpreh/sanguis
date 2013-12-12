#include <sanguis/gui/click_callback.hpp>
#include <sanguis/gui/default_aspect.hpp>
#include <sanguis/gui/get_focus.hpp>
#include <sanguis/gui/aux_/fill_rect.hpp>
#include <sanguis/gui/widget/base.hpp>
#include <sanguis/gui/widget/button.hpp>
#include <sge/font/align_h.hpp>
#include <sge/font/metrics.hpp>
#include <sge/font/object.hpp>
#include <sge/font/rect.hpp>
#include <sge/font/string.hpp>
#include <sge/font/unit.hpp>
#include <sge/font/text_parameters.hpp>
#include <sge/font/vector.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/rucksack/aspect.hpp>
#include <sge/rucksack/axis_policy.hpp>
#include <sge/rucksack/axis_policy2.hpp>
#include <sge/rucksack/is_expanding.hpp>
#include <sge/rucksack/minimum_size.hpp>
#include <sge/rucksack/optional_scalar.hpp>
#include <sge/rucksack/preferred_size.hpp>
#include <sge/rucksack/scalar.hpp>
#include <sge/rucksack/vector.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_impl.hpp>


namespace
{

sge::rucksack::scalar const
inner_border(
	fcppt::literal<
		sge::rucksack::scalar
	>(
		4
	)
);

sge::rucksack::scalar const
outer_border(
	fcppt::literal<
		sge::rucksack::scalar
	>(
		2
	)
);

sge::rucksack::scalar const
spacing(
	(
		inner_border
		+
		outer_border
	)
	*
	fcppt::literal<
		sge::rucksack::scalar
	>(
		2
	)
);

}

sanguis::gui::widget::button::button(
	sge::renderer::device::ffp &_renderer,
	sge::font::object &_font,
	sge::font::string const &_text
)
:
	sanguis::gui::widget::base(),
	renderer_(
		_renderer
	),
	static_text_(
		_renderer,
		_font,
		_text,
		sge::font::text_parameters(
			sge::font::align_h::center
		),
		sge::font::vector::null(),
		sge::image::color::predef::white(),
		sge::renderer::texture::emulate_srgb::no
	),
	font_size_(
		static_text_.rect().w(),
		_font.metrics().height().get()
	),
	layout_(
		sge::rucksack::axis_policy2(
			sge::rucksack::axis_policy(
				sge::rucksack::minimum_size(
					font_size_.w()
					+
					spacing
				),
				sge::rucksack::preferred_size(
					sge::rucksack::optional_scalar()
				),
				sge::rucksack::is_expanding(
					false
				)
			),
			sge::rucksack::axis_policy(
				sge::rucksack::minimum_size(
					font_size_.h()
					+
					spacing
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
	),
	click_()
{
}

sanguis::gui::widget::button::~button()
{
}

fcppt::signal::auto_connection
sanguis::gui::widget::button::click(
	sanguis::gui::click_callback const &_callback
)
{
	return
		click_.connect(
			_callback
		);
}

sge::rucksack::widget::base &
sanguis::gui::widget::button::layout()
{
	return
		layout_;
}

void
sanguis::gui::widget::button::on_draw(
	sge::renderer::context::ffp &_context
)
{
	sanguis::gui::aux_::fill_rect(
		renderer_,
		_context,
		sge::rucksack::rect(
			layout_.position(),
			font_size_
			+
			spacing
		),
		sge::image::color::predef::black()
	);

	sanguis::gui::aux_::fill_rect(
		renderer_,
		_context,
		sge::rucksack::rect(
			layout_.position()
			+
			inner_border,
			font_size_
			+
			inner_border
		),
		sge::image::color::predef::red()
	);

	static_text_.pos(
		fcppt::math::vector::structure_cast<
			sge::rucksack::vector
		>(
			layout_.position()
			+
			outer_border
			+
			inner_border
		)
	);

	static_text_.draw(
		_context
	);
}

sanguis::gui::get_focus const
sanguis::gui::widget::button::on_click(
	sge::rucksack::vector
)
{
	click_();

	return
		sanguis::gui::get_focus(
			true
		);
}
