#include <sanguis/client/perk/const_tree_range.hpp>
#include <sanguis/client/perk/tree.hpp>

sanguis::client::perk::const_tree_range::const_tree_range(
    sanguis::client::perk::tree::const_iterator const _begin,
    sanguis::client::perk::tree::const_iterator const _end)
    : begin_(_begin), end_(_end)
{
}

sanguis::client::perk::const_tree_range::const_tree_range(pair const &_pair)
    : begin_(_pair.first), end_(_pair.second)
{
}

sanguis::client::perk::tree::const_iterator sanguis::client::perk::const_tree_range::begin() const
{
  return begin_;
}

sanguis::client::perk::tree::const_iterator sanguis::client::perk::const_tree_range::end() const
{
  return end_;
}

bool sanguis::client::perk::const_tree_range::empty() const { return this->begin() == this->end(); }
