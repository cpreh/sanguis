#include <sanguis/client/gui/perk/state.hpp>
#include <sanguis/gui/widget/unique_ptr_vector.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


namespace
{

sanguis::client::gui::perk::line_unique_ptr_tree
make_tab(
	sanguis::client::perk::const_tree_range const _range
)
{
	sanguis::client::gui::perk::line_unique_ptr_tree result;

	for(
		auto const &top_element
		:
		_range
	)
	{
		for(
			auto const &element
			:
			fcppt::container::tree::pre_order<
				sanguis::client::perk::tree const
			>(
				top_element
			)
		)
		{
			if(
				element.parent()->value().has_value()
			)
				fcppt::algorithm::find_if_exn(
					fcppt::container::tree::pre_order<
						sanguis::gui::widget::unique_ptr_tree
					>(
						result
					),
					[](
						sanguis::client::gui::perk::line const &_line
					)
					{
						return
							_line.perk_type()
							==
							element.value()->type();
					}
				)->push_back(
					fcppt::make_unique_ptr<
						sanguis::client::gui::perk::line
					>(
						*element.value()
					)
				);
			else
				result.push_back(
					fcppt::make_unique_ptr<
						perk_line
					>(
						element.value()
					)
				);
		}
	}

	return
		std::move(
			result
		);
}

typedef
std::pair<
	sanguis::client::perk::tree::iterator,
	sanguis::client::perk::tree::iterator
>
equal_range_pair;

sanguis::gui::widget::unique_ptr_tree
make_tabs(
	sanguis::client::perk::state const &_perk_state
)
{
	for(
		iterator_pair const range(
			sanguis::client::perk::category_equal_range(
				tree.begin(),
				tree.end()
			)
		);
		range.first != range.second;
		range =
			sanguis::client::perk::category_equal_range(
				range.second,
				tree.end()
			)
	)
		result.push_back(
			make_tab(
				range
			)
		);

	return
		std::move(
			result
		);
}

}

sanguis::client::gui::perk::state::state()
:
	tabs_(
		make_tabs_(
			_state
		)
	)
{
}

sanguis::client::gui::perk::state::~state()
{
}
