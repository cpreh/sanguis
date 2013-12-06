#include <sanguis/gui/text_callback.hpp>
#include <sanguis/gui/text_function.hpp>
#include <sanguis/gui/widget/base.hpp>
#include <sanguis/gui/widget/edit.hpp>
#include <sge/font/align_h.hpp>
#include <sge/font/char_type.hpp>
#include <sge/font/object_fwd.hpp>
#include <sge/font/string.hpp>
#include <sge/font/text_parameters.hpp>
#include <sge/font/vector.hpp>
#include <sge/font/draw/simple.hpp>
#include <sge/image/color/predef.hpp>
#include <sge/input/keyboard/key_code.hpp>
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
#include <sge/rucksack/widget/base_fwd.hpp>
#include <sge/rucksack/widget/dummy.hpp>
#include <sge/rucksack/widget/optional_parent.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/math/vector/structure_cast.hpp>
#include <fcppt/signal/auto_connection.hpp>
#include <fcppt/signal/object_impl.hpp>


sanguis::gui::widget::edit::edit(
	sanguis::gui::widget::base &_parent,
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
					42 // TODO: Font height here!
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
	text_change_()
{
	layout_.parent(
		sge::rucksack::widget::optional_parent(
			_parent.layout()
		)
	);
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

void
sanguis::gui::widget::edit::on_update()
{
	// TODO: Show cursor
}

void
sanguis::gui::widget::edit::on_draw(
	sge::renderer::context::ffp &_context
)
{
	// TODO: Paint background
	sge::font::draw::simple(
		renderer_,
		_context,
		font_,
		text_,
		sge::font::text_parameters(
			sge::font::align_h::left
		),
		fcppt::math::vector::structure_cast<
			sge::font::vector
		>(
			layout_.position()
		),
		sge::image::color::predef::white(),
		sge::renderer::texture::emulate_srgb::no
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

		this->text_change();

		break;
	case sge::input::keyboard::key_code::right:
		if(
			position_ < text_.size()
		)
			++position_;

		this->text_change();

		break;
	case sge::input::keyboard::key_code::delete_:
		if(
			position_ != text_.size()
		)
			text_.erase(
				position_,
				1u
			);

		this->text_change();

		break;
	case sge::input::keyboard::key_code::backspace:
		if(
			position_ - 1u
			< text_.size()
		)
			text_.erase(
				position_ - 1u,
				1u
			);

		this->text_change();

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
	text_.insert(
		position_,
		1u,
		_char
	);

	++position_;

	this->text_change();
}

sge::rucksack::widget::base &
sanguis::gui::widget::edit::layout()
{
	return
		layout_;
}

void
sanguis::gui::widget::edit::text_change()
{
	text_change_(
		this->text()
	);
}
