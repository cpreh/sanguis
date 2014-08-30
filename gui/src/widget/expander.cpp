#include <sanguis/gui/widget/dummy.hpp>
#include <sanguis/gui/widget/expander.hpp>
#include <sge/rucksack/axis.hpp>
#include <sge/rucksack/axis_policy.hpp>
#include <sge/rucksack/make_axis_policy.hpp>
#include <sge/rucksack/minimum_size.hpp>
#include <sge/rucksack/preferred_size.hpp>
#include <sge/rucksack/scalar.hpp>
#include <sge/rucksack/widget/base_fwd.hpp>
#include <fcppt/literal.hpp>


sanguis::gui::widget::expander::expander(
	sge::rucksack::axis const _axis
)
:
	sanguis::gui::widget::dummy(),
	layout_{
		sge::rucksack::make_axis_policy(
			[
				_axis
			](
				sge::rucksack::axis const _cur_axis
			)
			{
				sge::rucksack::scalar const size{
					fcppt::literal<
						sge::rucksack::scalar
					>(
						0
					)
				};

				return
					_cur_axis
					==
					_axis
					?
						sge::rucksack::axis_policy{
							sge::rucksack::minimum_size{
								size
							}
						}
					:
						sge::rucksack::axis_policy{
							sge::rucksack::preferred_size{
								size
							}
						}
					;
			}
		)
	}
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
