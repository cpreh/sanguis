#include <sanguis/gui/fixed_area.hpp>
#include <sge/rucksack/rect.hpp>
#include <sge/rucksack/widget/base.hpp>


sanguis::gui::fixed_area::fixed_area(
	sge::rucksack::rect const _rect,
	sge::rucksack::widget::base &_widget
)
{
	_widget.position(
		_rect.pos()
	);

	_widget.size(
		_rect.size()
	);

	_widget.relayout();
}

sanguis::gui::fixed_area::~fixed_area()
{
}
