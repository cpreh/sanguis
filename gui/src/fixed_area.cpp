#include <sanguis/gui/fixed_area.hpp>
#include <sanguis/gui/widget/base.hpp>
#include <sge/rucksack/rect.hpp>
#include <sge/rucksack/widget/base.hpp>


sanguis::gui::fixed_area::fixed_area(
	sanguis::gui::widget::base &_widget,
	sge::rucksack::rect const _rect
)
{
	sge::rucksack::widget::base &layout(
		_widget.layout()
	);

	layout.position(
		_rect.pos()
	);

	layout.size(
		_rect.size()
	);

	layout.relayout();
}

sanguis::gui::fixed_area::~fixed_area()
{
}
