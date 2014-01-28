#include <sanguis/gui/fixed_area.hpp>
#include <sanguis/gui/widget/base.hpp>
#include <sge/rucksack/rect.hpp>
#include <sge/rucksack/vector.hpp>
#include <sge/rucksack/widget/base.hpp>


sanguis::gui::fixed_area::fixed_area(
	sanguis::gui::widget::base &_widget,
	sge::rucksack::rect const _rect
)
:
	layout_(
		_widget.layout()
	)
{
	layout_.size(
		_rect.size()
	);

	this->position(
		_rect.pos()
	);
}

sanguis::gui::fixed_area::~fixed_area()
{
}

void
sanguis::gui::fixed_area::position(
	sge::rucksack::vector const _pos
)
{
	layout_.position(
		_pos
	);

	layout_.relayout();
}

sge::rucksack::rect const
sanguis::gui::fixed_area::area() const
{
	return
		layout_.area();
}
