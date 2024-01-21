#ifndef SANGUIS_CLIENT_PERK_CONST_TREE_RANGE_HPP_INCLUDED
#define SANGUIS_CLIENT_PERK_CONST_TREE_RANGE_HPP_INCLUDED

#include <sanguis/client/perk/const_tree_range_fwd.hpp> // IWYU pragma: keep
#include <sanguis/client/perk/tree.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

namespace sanguis::client::perk
{

class const_tree_range
{
public:
  const_tree_range(
      sanguis::client::perk::tree::const_iterator, sanguis::client::perk::tree::const_iterator);

  using pair = std::pair<
      sanguis::client::perk::tree::const_iterator,
      sanguis::client::perk::tree::const_iterator>;

  explicit const_tree_range(pair const &);

  [[nodiscard]] sanguis::client::perk::tree::const_iterator begin() const;

  [[nodiscard]] sanguis::client::perk::tree::const_iterator end() const;

  [[nodiscard]] bool empty() const;

private:
  sanguis::client::perk::tree::const_iterator begin_;

  sanguis::client::perk::tree::const_iterator end_;
};

}

#endif
