#include <sanguis/server/buffs/buff.hpp>
#include <sanguis/server/buffs/comparator.hpp>
#include <sanguis/server/buffs/unique_ptr.hpp>

bool sanguis::server::buffs::comparator::operator()(
    sanguis::server::buffs::unique_ptr const &_left,
    sanguis::server::buffs::unique_ptr const &_right) const
{
  return _left->greater(*_right);
}

bool sanguis::server::buffs::comparator::operator()(
    sanguis::server::buffs::unique_ptr const &_left,
    sanguis::server::buffs::buff const &_right) const
{
  return _left->greater(_right);
}

bool sanguis::server::buffs::comparator::operator()(
    sanguis::server::buffs::buff const &_left,
    sanguis::server::buffs::unique_ptr const &_right) const
{
  return _left.greater(*_right);
}
