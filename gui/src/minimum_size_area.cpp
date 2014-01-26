#include <sanguis/gui/minimum_size_area.hpp>
#include <sanguis/gui/widget/base.hpp>
#include <sge/rucksack/vector.hpp>


sanguis::gui::minimum_size_area::minimum_size_area(
	sanguis::gui::widget::base &_widget,
	sge::rucksack::vector const _pos
)
:
	layout_(
		_widget.layout()
	)
{
	layout_.position(
		_pos
	);

	this->relayout();
}

sanguis::gui::minimum_size_area::~minimum_size_area()
{
}

void
sanguis::gui::minimum_size_area::relayout()
{
	layout_.relayout();
}
