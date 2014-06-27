#include <sanguis/gui/default_aspect.hpp>
#include <sanguis/gui/widget/dummy.hpp>
#include <sanguis/gui/widget/expander.hpp>
#include <sge/rucksack/axis.hpp>
#include <sge/rucksack/axis_policy.hpp>
#include <sge/rucksack/axis_policy2.hpp>
#include <sge/rucksack/is_expanding.hpp>
#include <sge/rucksack/minimum_size.hpp>
#include <sge/rucksack/optional_scalar.hpp>
#include <sge/rucksack/preferred_size.hpp>
#include <sge/rucksack/scalar.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <fcppt/literal.hpp>


sanguis::gui::widget::expander::expander(
	sge::rucksack::axis const _axis
)
:
	sanguis::gui::widget::dummy(),
	layout_(
		sge::rucksack::axis_policy2(
			sge::rucksack::axis_policy(
				sge::rucksack::minimum_size(
					fcppt::literal<
						sge::rucksack::scalar
					>(
						0
					)
				),
				sge::rucksack::preferred_size(
					sge::rucksack::optional_scalar()
				),
				sge::rucksack::is_expanding(
					_axis
					==
					sge::rucksack::axis::x
				)
			),
			sge::rucksack::axis_policy(
				sge::rucksack::minimum_size(
					fcppt::literal<
						sge::rucksack::scalar
					>(
						0
					)
				),
				sge::rucksack::preferred_size(
					sge::rucksack::optional_scalar()
				),
				sge::rucksack::is_expanding(
					_axis
					==
					sge::rucksack::axis::y
				)
			),
			sanguis::gui::default_aspect()
		)
	)
{
}

sanguis::gui::widget::expander::~expander()
{
}

sge::rucksack::widget::base &
sanguis::gui::widget::expander::layout()
{
	return
		layout_;
}
