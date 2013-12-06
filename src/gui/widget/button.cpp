#include <sanguis/gui/click_callback.hpp>
#include <sanguis/gui/get_focus.hpp>
#include <sanguis/gui/widget/base.hpp>
#include <sanguis/gui/widget/button.hpp>
#include <sge/font/align_h.hpp>
#include <sge/font/object_fwd.hpp>
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
#include <sge/rucksack/widget/optional_parent.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_impl.hpp>


sanguis::gui::widget::button::button(
	sanguis::gui::widget::base &_parent,
	sge::renderer::device::ffp &_renderer,
	sge::font::object &_font,
	sge::font::string const &_text
)
:
	sanguis::gui::widget::base(),
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
	layout_(
		sge::rucksack::axis_policy2(
			sge::rucksack::axis_policy(
				sge::rucksack::minimum_size(
					static_cast<
						sge::font::unit
					>(
						static_text_.rect().w()
					)
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
					static_cast<
						sge::font::unit
					>(
						static_text_.rect().h()
					)
				),
				sge::rucksack::preferred_size(
					sge::rucksack::optional_scalar()
				),
				sge::rucksack::is_expanding(
					false
				)
			),
			sge::rucksack::aspect(
				fcppt::literal<
					sge::rucksack::scalar
				>(
					1
				),
				fcppt::literal<
					sge::rucksack::scalar
				>(
					1
				)
			)
		)
	),
	click_()
{
	layout_.parent(
		sge::rucksack::widget::optional_parent(
			_parent.layout()
		)
	);
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

void
sanguis::gui::widget::button::on_draw(
	sge::renderer::context::ffp &_context
)
{
	static_text_.pos(
		fcppt::math::vector::structure_cast<
			sge::rucksack::vector
		>(
			layout_.position()
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

sge::rucksack::widget::base &
sanguis::gui::widget::button::layout()
{
	return
		layout_;
}
