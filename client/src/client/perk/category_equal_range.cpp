#include <sanguis/exception.hpp>
#include <sanguis/client/perk/category_equal_range.hpp>
#include <sanguis/client/perk/const_tree_range.hpp>
#include <sanguis/client/perk/info.hpp>
#include <sanguis/client/perk/to_category.hpp>
#include <sanguis/client/perk/tree.hpp>
#include <fcppt/text.hpp>
#include <fcppt/optional/to_exception.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <fcppt/config/external_end.hpp>

sanguis::client::perk::const_tree_range sanguis::client::perk::category_equal_range(
    sanguis::client::perk::tree::const_iterator const _begin,
    sanguis::client::perk::tree::const_iterator const _end)
{
  return _begin == _end
             ? sanguis::client::perk::const_tree_range(_begin, _end)
             : sanguis::client::perk::const_tree_range(std::equal_range(
                   _begin,
                   _end,
                   *_begin,
                   [](sanguis::client::perk::tree const &_left,
                      sanguis::client::perk::tree const &_right)
                   {
                     return sanguis::client::perk::to_category(
                                fcppt::optional::to_exception(
                                    _left.value(),
                                    [] {
                                      return sanguis::exception{FCPPT_TEXT("Perk type not set!")};
                                    })
                                    .perk_type()) <
                            sanguis::client::perk::to_category(
                                fcppt::optional::to_exception(
                                    _right.value(),
                                    [] {
                                      return sanguis::exception{FCPPT_TEXT("Perk type not set!")};
                                    })
                                    .perk_type());
                   }));
}
