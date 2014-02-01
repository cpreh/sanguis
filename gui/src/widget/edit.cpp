#include <sanguis/gui/default_aspect.hpp>
#include <sanguis/gui/duration.hpp>
#include <sanguis/gui/get_focus.hpp>
#include <sanguis/gui/text_callback.hpp>
#include <sanguis/gui/text_function.hpp>
#include <sanguis/gui/aux_/fill_rect.hpp>
#include <sanguis/gui/aux_/style/background_color.hpp>
#include <sanguis/gui/aux_/style/border_color.hpp>
#include <sanguis/gui/aux_/style/outer_border.hpp>
#include <sanguis/gui/aux_/style/spacing.hpp>
#include <sanguis/gui/aux_/style/text_color.hpp>
#include <sanguis/gui/widget/base.hpp>
#include <sanguis/gui/widget/edit.hpp>
#include <sge/font/char_type.hpp>
#include <sge/font/dim.hpp>
#include <sge/font/flags.hpp>
#include <sge/font/flags_field.hpp>
#include <sge/font/metrics.hpp>
#include <sge/font/object.hpp>
#include <sge/font/optional_index.hpp>
#include <sge/font/rect.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text.hpp>
#include <sge/font/text_parameters.hpp>
#include <sge/font/unit.hpp>
#include <sge/font/v_center.hpp>
#include <sge/font/vector.hpp>
#include <sge/font/align_h/left.hpp>
#include <sge/font/align_h/max_width.hpp>
#include <sge/font/draw/static_text.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/renderer/texture/emulate_srgb.hpp>
#include <sge/rucksack/axis_policy.hpp>
#include <sge/rucksack/axis_policy2.hpp>
#include <sge/rucksack/is_expanding.hpp>
#include <sge/rucksack/minimum_size.hpp>
#include <sge/rucksack/optional_scalar.hpp>
#include <sge/rucksack/preferred_size.hpp>
#include <sge/rucksack/rect.hpp>
#include <sge/rucksack/scalar.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <sge/rucksack/widget/dummy.hpp>
#include <sge/timer/basic_impl.hpp>
#include <sge/timer/reset_when_expired.hpp>
#include <sge/timer/clocks/delta_impl.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/string_conv_locale.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/math/dim/arithmetic.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <locale>
#include <fcppt/config/external_end.hpp>


sanguis::gui::widget::edit::edit(
	sge::renderer::device::ffp &_renderer,
	sge::font::object &_font,
	sge::font::string const &_text
)
:
	sanguis::gui::widget::base(),
	renderer_(
		_renderer
	),
	font_(
		_font
	),
	text_(
		_text
	),
	position_(
		0u
	),
	layout_(
		sge::rucksack::axis_policy2(
			sge::rucksack::axis_policy(
				sge::rucksack::minimum_size(
					fcppt::literal<
						sge::rucksack::scalar
					>(
						0
					)
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
					+
					sanguis::gui::aux_::style::spacing::value
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
	static_text_(
		this->make_static_text()
	),
	clock_(),
	cursor_blink_timer_(
		diff_timer::parameters(
			clock_,
			std::chrono::milliseconds(
				500
			)
		)
	),
	has_focus_(
		false
	),
	show_cursor_(
		true
	),
	text_change_()
{
}

sanguis::gui::widget::edit::~edit()
{
}

sge::font::string const &
sanguis::gui::widget::edit::text() const
{
	return
		text_;
}

fcppt::signal::auto_connection
sanguis::gui::widget::edit::text_change(
	sanguis::gui::text_callback const &_callback
)
{
	return
		text_change_.connect(
			_callback
		);
}

sge::rucksack::widget::base &
sanguis::gui::widget::edit::layout()
{
	return
		layout_;
}

void
sanguis::gui::widget::edit::on_update(
	sanguis::gui::duration const _duration
)
{
	if(
		!has_focus_
	)
		return;

	clock_.update(
		_duration
	);

	if(
		sge::timer::reset_when_expired(
			cursor_blink_timer_
		)
	)
		show_cursor_ =
			!show_cursor_;
}

void
sanguis::gui::widget::edit::on_draw(
	sge::renderer::context::ffp &_context
)
{
	// TODO: Add a signal to sge that tells us when a layout changes
	static_text_ =
		this->make_static_text();

	sanguis::gui::aux_::fill_rect(
		renderer_,
		_context,
		sge::rucksack::rect(
			layout_.position(),
			layout_.size()
		),
		sanguis::gui::aux_::style::border_color()
	);

	sanguis::gui::aux_::fill_rect(
		renderer_,
		_context,
		sge::rucksack::rect(
			layout_.position()
			+
			sanguis::gui::aux_::style::outer_border::value,
			layout_.size()
			-
			2
			*
			sanguis::gui::aux_::style::outer_border::value
		),
		sanguis::gui::aux_::style::background_color()
	);

	static_text_.draw(
		_context
	);

	if(
		!has_focus_
		||
		!show_cursor_
	)
		return;

	sge::font::rect const cursor_rect(
		static_text_.text().cursor_rect(
			position_
		)
	);

	sanguis::gui::aux_::fill_rect(
		renderer_,
		_context,
		sge::rucksack::rect(
			cursor_rect.pos()
			+
			static_text_.pos(),
			sge::font::dim(
				// TODO: How do we specify the width?
				2,
				cursor_rect.h()
			)
		),
		sanguis::gui::aux_::style::text_color()
	);
}

sanguis::gui::get_focus const
sanguis::gui::widget::edit::on_click(
	sge::rucksack::vector const _pos
)
{
	sge::font::optional_index const index(
		static_text_.text().pos_to_index(
			fcppt::math::vector::structure_cast<
				sge::font::vector
			>(
				_pos
				-
				static_text_.pos()
			)
		)
	);

	if(
		index
	)
	{
		FCPPT_ASSERT_ERROR(
			*index
			<=
			text_.size()
		);

		position_ =
			*index;
	}
	else if(
		_pos.x()
		>=
		static_text_.rect().w()
		+
		static_text_.pos().x()
	)
		position_
			= text_.size();

	return
		sanguis::gui::get_focus(
			true
		);
}

void
sanguis::gui::widget::edit::on_key(
	sge::input::keyboard::key_code const _code
)
{
	switch(
		_code
	)
	{
	case sge::input::keyboard::key_code::left:
		if(
			position_ != 0u
		)
			--position_;

		break;
	case sge::input::keyboard::key_code::right:
		if(
			position_ < text_.size()
		)
			++position_;

		break;
	case sge::input::keyboard::key_code::delete_:
		if(
			position_ != text_.size()
		)
		{
			text_.erase(
				position_,
				1u
			);

			this->text_changed();
		}

		break;
	case sge::input::keyboard::key_code::backspace:
		if(
			position_ - 1u
			<
			text_.size()
		)
		{
			text_.erase(
				position_ - 1u,
				1u
			);

			--position_;

			this->text_changed();
		}

		break;
	default:
		break;
	}
}

void
sanguis::gui::widget::edit::on_char(
	sge::font::char_type const _char
)
{
	if(
		!std::isprint(
			_char,
			fcppt::string_conv_locale()
		)
	)
		return;

	text_.insert(
		position_,
		1u,
		_char
	);

	++position_;

	this->text_changed();
}

void
sanguis::gui::widget::edit::on_focus_changed(
	bool const _has_focus
)
{
	has_focus_ =
		_has_focus;

	if(
		has_focus_
	)
	{
		show_cursor_ =
			true;

		cursor_blink_timer_.reset();
	}
}

sge::font::draw::static_text
sanguis::gui::widget::edit::make_static_text()
{
	return
		sge::font::draw::static_text(
			renderer_,
			font_,
			text_,
			sge::font::text_parameters(
				sge::font::align_h::left(
					sge::font::align_h::max_width(
						std::max(
							layout_.size().w()
							-
							2
							*
							sanguis::gui::aux_::style::spacing::value,
							fcppt::literal<
								sge::font::unit
							>(
								0
							)
						)
					)
				)
			)
			// FIXME: no_multi_line does something weird in pango
			/*
			.flags(
				sge::font::flags_field{
					sge::font::flags::no_multi_line
				}
			)*/,
			fcppt::math::vector::structure_cast<
				sge::font::vector
			>(
				layout_.position()
				+
				sanguis::gui::aux_::style::inner_border::value
				+
				sanguis::gui::aux_::style::outer_border::value
			)
			+
			sge::font::vector(
				0,
				sge::font::v_center(
					font_.metrics().height(),
					layout_.size().h()
					-
					sanguis::gui::aux_::style::spacing::value
				)
			),
			sanguis::gui::aux_::style::text_color(),
			sge::renderer::texture::emulate_srgb::no
		);
}

void
sanguis::gui::widget::edit::text_changed()
{
	static_text_ =
		this->make_static_text();

	text_change_(
		this->text()
	);
}
