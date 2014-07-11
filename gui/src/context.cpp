#include <sanguis/gui/context.hpp>
#include <sanguis/gui/focus_change.hpp>
#include <sanguis/gui/widget/base.hpp>
#include <sanguis/gui/widget/optional_ref.hpp>
#include <fcppt/assert/error.hpp>


sanguis::gui::context::context()
:
	focus_()
{
}

sanguis::gui::context::~context()
{
	FCPPT_ASSERT_ERROR(
		!focus_
	);
}

void
sanguis::gui::context::focus(
	sanguis::gui::widget::base &_widget
)
{
	if(
		focus_
	)
		focus_->on_focus_changed(
			sanguis::gui::focus_change::lost
		);

	focus_ =
		sanguis::gui::widget::optional_ref(
			_widget
		);

	_widget.on_focus_changed(
		sanguis::gui::focus_change::gained
	);
}

void
sanguis::gui::context::destroy(
	sanguis::gui::widget::base const &_widget
)
{
	if(
		focus_
		&&
		&*focus_
		==
		&_widget
	)
		focus_ =
			sanguis::gui::widget::optional_ref();
}

sanguis::gui::widget::optional_ref const
sanguis::gui::context::focus() const
{
	return
		focus_;
}
