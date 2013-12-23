#include <sanguis/gui/duration.hpp>
#include <sanguis/gui/get_focus.hpp>
#include <sanguis/gui/widget/base.hpp>
#include <sanguis/gui/widget/optional_ref.hpp>
#include <sge/font/char_type.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <sge/rucksack/vector.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <sge/rucksack/widget/optional_parent.hpp>


sanguis::gui::widget::base::base()
:
	parent_(),
	enabled_(
		true
	)
{
}

sanguis::gui::widget::base::~base()
{
	if(
		parent_
	)
		parent_->unregister(
			*this
		);
}

void
sanguis::gui::widget::base::on_update(
	sanguis::gui::duration
)
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

void
sanguis::gui::widget::base::parent(
	sanguis::gui::widget::optional_ref const _parent
)
{
	if(
		parent_
	)
		this->layout().parent(
			sge::rucksack::widget::optional_parent()
		);

	parent_ =
		_parent;

	if(
		_parent
	)
		this->layout().parent(
			sge::rucksack::widget::optional_parent(
				_parent->layout()
			)
		);
}

void
sanguis::gui::widget::base::enable(
	bool const _enabled
)
{
	enabled_ =
		_enabled;
}

bool
sanguis::gui::widget::base::enabled() const
{
	return
		enabled_;
}

void
sanguis::gui::widget::base::unregister(
	sanguis::gui::widget::base const &
)
{
}
