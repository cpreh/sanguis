#include <sanguis/gui/widget/base.hpp>
#include <sanguis/gui/widget/dummy.hpp>
#include <sge/renderer/context/ffp_fwd.hpp>
#include <sge/rucksack/axis_policy2_fwd.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <sge/rucksack/widget/dummy.hpp>


sanguis::gui::widget::dummy::dummy(
	sge::rucksack::axis_policy2 const &_policy
)
:
	sanguis::gui::widget::base(),
	layout_(
		_policy
	)
{
}

sanguis::gui::widget::dummy::~dummy()
{
}

void
sanguis::gui::widget::dummy::on_draw(
	sge::renderer::context::ffp &
)
{
}

sge::rucksack::widget::base &
sanguis::gui::widget::dummy::layout()
{
	return
		layout_;
}
