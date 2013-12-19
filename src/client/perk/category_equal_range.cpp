#include <sanguis/client/perk/const_tree_range.hpp>
#include <sanguis/client/perk/category_equal_range.hpp>
#include <sanguis/client/perk/info.hpp>
#include <sanguis/client/perk/to_category.hpp>
#include <sanguis/client/perk/tree.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>


sanguis::client::perk::const_tree_range const
sanguis::client::perk::category_equal_range(
	sanguis::client::perk::tree::const_iterator const _begin,
	sanguis::client::perk::tree::const_iterator const _end
)
{
	return
		_begin
		==
		_end
		?
			sanguis::client::perk::const_tree_range(
				_begin,
				_end
			)
		:
			std::equal_range(
				_begin,
				_end,
				[
					_begin
				](
					sanguis::gui::perk::info const &_info
				)
				{
					return
						_begin->perk_type()
						<
						sanguis::gui::perk::to_category(
							_info.perk_type()
						);
				}
			)
		;
}
