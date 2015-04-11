#include <sanguis/gui/duration.hpp>
#include <sanguis/gui/focus_change.hpp>
#include <sanguis/gui/get_focus.hpp>
#include <sanguis/gui/widget/base.hpp>
#include <sanguis/gui/widget/optional_focus.hpp>
#include <sanguis/gui/widget/optional_ref.hpp>
#include <sge/font/char_type.hpp>
#include <sge/input/keyboard/key_code.hpp>
#include <sge/rucksack/vector.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <sge/rucksack/widget/optional_ref.hpp>
#include <fcppt/maybe_void.hpp>


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
	fcppt::maybe_void(
		parent_,
		[
			this
		](
			sanguis::gui::widget::base &_parent
		)
		{
			_parent.unregister(
				*this
			);
		}
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
sanguis::gui::widget::base::on_focus_changed(
	sanguis::gui::focus_change
)
{
}

sanguis::gui::widget::optional_ref const
sanguis::gui::widget::base::on_tab(
	sanguis::gui::widget::optional_focus &
)
{
	return
		sanguis::gui::widget::optional_ref();
}

void
sanguis::gui::widget::base::parent(
	sanguis::gui::widget::optional_ref const _new_parent
)
{
	if(
		parent_.has_value()
	)
		this->layout().parent(
			sge::rucksack::widget::optional_ref()
		);

	parent_ =
		_new_parent;

	fcppt::maybe_void(
		_new_parent,
		[
			this
		](
			sanguis::gui::widget::base &_parent
		)
		{
			this->layout().parent(
				sge::rucksack::widget::optional_ref(
					_parent.layout()
				)
			);
		}
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
