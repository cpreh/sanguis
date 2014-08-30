#include <sanguis/gui/click_callback.hpp>
#include <sanguis/gui/get_focus.hpp>
#include <sanguis/gui/optional_needed_width.hpp>
#include <sanguis/gui/renderer/base.hpp>
#include <sanguis/gui/style/base.hpp>
#include <sanguis/gui/widget/base.hpp>
#include <sanguis/gui/widget/button.hpp>
#include <sge/font/dim.hpp>
#include <sge/font/flags.hpp>
#include <sge/font/flags_field.hpp>
#include <sge/font/metrics.hpp>
#include <sge/font/object.hpp>
#include <sge/font/rect.hpp>
#include <sge/font/string.hpp>
#include <sge/font/unit.hpp>
#include <sge/font/text_parameters.hpp>
#include <sge/font/v_center.hpp>
#include <sge/font/vector.hpp>
#include <sge/font/align_h/left.hpp>
#include <sge/font/draw/static_text.hpp>
#include <sge/image/color/any/object.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/rucksack/axis_policy.hpp>
#include <sge/rucksack/axis_policy2.hpp>
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


sanguis::gui::widget::button::button(
	sanguis::gui::style::base const &_style,
	sge::renderer::device::ffp &_renderer,
	sge::font::object &_font,
	sge::font::string const &_text,
	sanguis::gui::optional_needed_width const _needed_width
)
:
	sanguis::gui::widget::base(),
	style_(
		_style
	),
	renderer_(
		_renderer
	),
	font_(
		_font
	),
	text_(
		_text
	),
	static_text_(
		this->make_static_text(
			_text
		)
	),
	layout_{
		sge::rucksack::axis_policy2{
			sge::rucksack::axis_policy{
				sge::rucksack::preferred_size{
					(
						_needed_width
						?
							_needed_width->get()
						:
							static_text_.logical_size().w()
					)
					+
					_style.button_spacing().w()
				}
			},
			sge::rucksack::axis_policy{
				sge::rucksack::preferred_size{
					_font.metrics().height().get()
					+
					_style.button_spacing().h()
				}
			}
		}
	},
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

sge::font::string const &
sanguis::gui::widget::button::text() const
{
	return
		text_;
}

void
sanguis::gui::widget::button::text(
	sge::font::string const &_text
)
{
	static_text_ =
		this->make_static_text(
			_text
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
	sanguis::gui::renderer::base &_renderer,
	sge::renderer::context::ffp &_context
)
{
	style_.draw_button(
		_renderer,
		_context,
		this->layout().area()
	);

	static_text_.pos(
		fcppt::math::vector::structure_cast<
			sge::font::vector
		>(
			layout_.position()
			+
			style_.button_spacing()
			/
			2
		)
		+
		sge::font::vector(
			0,
			sge::font::v_center(
				font_.metrics().height(),
				layout_.size().h()
				-
				style_.button_spacing().h()
			)
		)
	);

	_renderer.draw_static_text(
		_context,
		static_text_
	);
}

sanguis::gui::get_focus const
sanguis::gui::widget::button::on_click(
	sge::rucksack::vector
)
{
	if(
		!this->enabled()
	)
		return
			sanguis::gui::get_focus(
				false
			);

	click_();

	return
		sanguis::gui::get_focus(
			true
		);
}

sge::font::draw::static_text
sanguis::gui::widget::button::make_static_text(
	sge::font::string const &_text
)
{
	return
		sge::font::draw::static_text(
			renderer_,
			font_,
			_text,
			sge::font::text_parameters(
				sge::font::align_h::left()
			)
			.flags(
				sge::font::flags_field{
					sge::font::flags::no_multi_line
				}
			),
			sge::font::vector::null(),
			style_.text_color().get(),
			sge::renderer::texture::emulate_srgb::no
		);
}
