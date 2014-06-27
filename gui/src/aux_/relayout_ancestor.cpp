#include <sanguis/gui/aux_/relayout_ancestor.hpp>
#include <sanguis/gui/widget/base.hpp>
#include <sge/rucksack/widget/base.hpp>
#include <sge/rucksack/widget/optional_parent.hpp>


void
sanguis::gui::aux_::relayout_ancestor(
	sanguis::gui::widget::base &_widget
)
{
	sge::rucksack::widget::optional_parent layout(
		_widget.layout()
	);

	while(
		layout->parent()
	)
		layout =
			layout->parent();

	layout->relayout();
}
