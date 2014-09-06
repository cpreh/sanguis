#include <sanguis/gui/widget/base.hpp>
#include <sanguis/gui/widget/dummy.hpp>
#include <sanguis/gui/widget/preferred_size.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <sge/rucksack/widget/dummy.hpp>
#include <sge/rucksack/axis_policy2.hpp>
#include <sge/rucksack/preferred_size.hpp>
#include <sge/rucksack/dim.hpp>


sanguis::gui::widget::preferred_size::preferred_size(
	sge::rucksack::dim const &_area
)
:
	sanguis::gui::widget::dummy(),
	layout_{
		sge::rucksack::axis_policy2{
			sge::rucksack::preferred_size{
				_area.w()
			},
			sge::rucksack::preferred_size{
				_area.h()
			}
		}
	}
{
}

sanguis::gui::widget::preferred_size::~preferred_size()
{
}

sge::rucksack::widget::base &
sanguis::gui::widget::preferred_size::layout()
{
	return
		layout_;
}
