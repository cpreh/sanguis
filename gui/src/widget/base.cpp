#include <sanguis/gui/get_focus.hpp>
#include <sanguis/gui/widget/base.hpp>
#include <sge/font/char_type.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <sge/rucksack/vector.hpp>


sanguis::gui::widget::base::base()
{
}

sanguis::gui::widget::base::~base()
{
}

void
sanguis::gui::widget::base::on_update()
{
}

sanguis::gui::get_focus const
sanguis::gui::widget::base::on_click(
	sge::rucksack::vector
)
{
	return
		sanguis::gui::get_focus(
			false
		);
}

void
sanguis::gui::widget::base::on_key(
	sge::input::keyboard::key_code
)
{
}

void
sanguis::gui::widget::base::on_char(
	sge::font::char_type
)
{
}
