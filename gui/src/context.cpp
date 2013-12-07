#include <sanguis/gui/context.hpp>
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
	focus_ =
		sanguis::gui::widget::optional_ref(
			_widget
		);
}

void
sanguis::gui::context::destroy(
	sanguis::gui::widget::base &_widget
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
