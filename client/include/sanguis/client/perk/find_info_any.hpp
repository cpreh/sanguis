#ifndef SANGUIS_CLIENT_PERK_FIND_INFO_ANY_HPP_INCLUDED
#define SANGUIS_CLIENT_PERK_FIND_INFO_ANY_HPP_INCLUDED

#include <sanguis/exception.hpp>
#include <sanguis/perk_type.hpp>
#include <sanguis/client/perk/compare.hpp>
#include <sanguis/client/perk/to_string.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/text.hpp>
#include <fcppt/algorithm/find_if_opt.hpp>
#include <fcppt/container/tree/pre_order.hpp>
#include <fcppt/optional/to_exception.hpp>

namespace sanguis::client::perk
{

template <typename Tree>
Tree &find_info_any(sanguis::perk_type const _type, fcppt::reference<Tree> const _tree)
{
  return *fcppt::optional::to_exception(
      fcppt::algorithm::find_if_opt(
          fcppt::container::tree::pre_order<Tree>(_tree.get()),
          sanguis::client::perk::compare(_type)),
      [_type]
      {
        return sanguis::exception{
            FCPPT_TEXT("Can't find perk type ") + sanguis::client::perk::to_string(_type)};
      });
}

}

#endif
