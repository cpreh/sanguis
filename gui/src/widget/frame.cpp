#include <sanguis/gui/focus_change.hpp>
#include <sanguis/gui/get_focus.hpp>
#include <sanguis/gui/aux_/fill_rect.hpp>
#include <sanguis/gui/aux_/style/border_color.hpp>
#include <sanguis/gui/widget/base.hpp>
#include <sanguis/gui/widget/frame.hpp>
#include <sanguis/gui/widget/optional_focus.hpp>
#include <sanguis/gui/widget/optional_ref.hpp>
#include <sge/font/char_type.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/renderer/device/ffp_fwd.hpp>
#include <sge/rucksack/dim.hpp>
#include <sge/rucksack/padding.hpp>
#include <sge/rucksack/rect.hpp>
#include <sge/rucksack/scalar.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>


sanguis::gui::widget::frame::frame(
	sge::renderer::device::ffp &_renderer,
	sanguis::gui::widget::base &_child
)
:
	sanguis::gui::widget::base(),
	renderer_(
		_renderer
	),
	child_(
		_child
	),
	layout_{
		_child.layout(),
		sge::rucksack::padding{
			10
		}
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
	sge::renderer::context::ffp &_context
)
{
	sge::rucksack::scalar const border_size(
		layout_.padding().get()
		/
		2
	);

	sanguis::gui::aux_::fill_rect(
		renderer_,
		_context,
		sge::rucksack::rect(
			this->layout().position(),
			sge::rucksack::dim(
				this->layout().size().w(),
				border_size
			)
		),
		sanguis::gui::aux_::style::border_color()
	);

	sanguis::gui::aux_::fill_rect(
		renderer_,
		_context,
		sge::rucksack::rect(
			this->layout().position(),
			sge::rucksack::dim(
				border_size,
				this->layout().size().h()
			)
		),
		sanguis::gui::aux_::style::border_color()
	);

	sanguis::gui::aux_::fill_rect(
		renderer_,
		_context,
		sge::rucksack::rect(
			this->layout().position()
			+
			sge::rucksack::dim(
				this->layout().size().w()
				-
				border_size,
				0
			),
			sge::rucksack::dim(
				border_size,
				this->layout().size().h()
			)
		),
		sanguis::gui::aux_::style::border_color()
	);

	sanguis::gui::aux_::fill_rect(
		renderer_,
		_context,
		sge::rucksack::rect(
			this->layout().position()
			+
			sge::rucksack::dim(
				0,
				this->layout().size().h()
				-
				border_size
			),
			sge::rucksack::dim(
				this->layout().size().w(),
				border_size
			)
		),
		sanguis::gui::aux_::style::border_color()
	);

	child_.on_draw(
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
