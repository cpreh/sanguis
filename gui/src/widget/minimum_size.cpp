#include <sanguis/gui/widget/base.hpp>
#include <sanguis/gui/widget/dummy.hpp>
#include <sanguis/gui/widget/minimum_size.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <sge/rucksack/widget/minimum_size.hpp>


sanguis::gui::widget::minimum_size::minimum_size(
	sanguis::gui::widget::base &_widget
)
:
	sanguis::gui::widget::dummy(),
	layout_(
		_widget.layout()
	)
{
}

sanguis::gui::widget::minimum_size::~minimum_size()
{
}

sge::rucksack::widget::base &
sanguis::gui::widget::minimum_size::layout()
{
	return
		layout_;
}
