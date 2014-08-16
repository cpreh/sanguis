#include <sanguis/gui/focus_change.hpp>
#include <sanguis/gui/get_focus.hpp>
#include <sanguis/gui/renderer/base_fwd.hpp>
#include <sanguis/gui/style/base.hpp>
#include <sanguis/gui/widget/base.hpp>
#include <sanguis/gui/widget/frame.hpp>
#include <sanguis/gui/widget/optional_focus.hpp>
#include <sanguis/gui/widget/optional_ref.hpp>
#include <sge/font/char_type.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/rucksack/padding.hpp>
#include <sge/rucksack/rect.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>


sanguis::gui::widget::frame::frame(
	sanguis::gui::style::base const &_style,
	sanguis::gui::widget::base &_child
)
:
	sanguis::gui::widget::base(),
	style_(
		_style
	),
	child_(
		_child
	),
	layout_{
		_child.layout(),
		_style.frame_padding()
	}
{
	child_.parent(
		sanguis::gui::widget::optional_ref(
			*this
		)
	);
}

sanguis::gui::widget::frame::~frame()
{
}

sge::rucksack::widget::base &
sanguis::gui::widget::frame::layout()
{
	return
		layout_;
}

void
sanguis::gui::widget::frame::on_draw(
	sanguis::gui::renderer::base &_renderer,
	sge::renderer::context::ffp &_context
)
{
	style_.draw_frame(
		_renderer,
		_context,
		this->layout().area(),
		layout_.padding()
	);

	child_.on_draw(
		_renderer,
		_context
	);
}

sanguis::gui::get_focus const
sanguis::gui::widget::frame::on_click(
	sge::rucksack::vector const _pos
)
{
	return
		child_.on_click(
			_pos
		);
}

void
sanguis::gui::widget::frame::on_key(
	sge::input::keyboard::key_code const _key
)
{
	return
		child_.on_key(
			_key
		);
}

void
sanguis::gui::widget::frame::on_char(
	sge::font::char_type const _char
)
{
	child_.on_char(
		_char
	);
}

void
sanguis::gui::widget::frame::on_focus_changed(
	sanguis::gui::focus_change const _change
)
{
	child_.on_focus_changed(
		_change
	);
}

sanguis::gui::widget::optional_ref const
sanguis::gui::widget::frame::on_tab(
	sanguis::gui::widget::optional_focus &_focus
)
{
	return
		child_.on_tab(
			_focus
		);
}
