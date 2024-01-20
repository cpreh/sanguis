#ifndef SANGUIS_SERVER_BUFFS_STACK_HPP_INCLUDED
#define SANGUIS_SERVER_BUFFS_STACK_HPP_INCLUDED

#include <sanguis/server/buffs/buff_fwd.hpp>
#include <sanguis/server/buffs/comparator.hpp>
#include <sanguis/server/buffs/stack_fwd.hpp> // IWYU pragma: keep
#include <sanguis/server/buffs/unique_ptr.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <set>
#include <fcppt/config/external_end.hpp>

namespace sanguis::server::buffs
{

class stack
{
  FCPPT_NONCOPYABLE(stack);

public:
  stack();

  stack(stack &&) noexcept;

  stack &operator=(stack &&) noexcept;

  ~stack();

  void insert(sanguis::server::buffs::unique_ptr &&);

  void erase(sanguis::server::buffs::buff const &);

  [[nodiscard]] bool empty() const;

  [[nodiscard]] sanguis::server::buffs::buff &highest_buff();

  [[nodiscard]] sanguis::server::buffs::buff const &highest_buff() const;

private:
  using set = std::multiset<sanguis::server::buffs::unique_ptr, sanguis::server::buffs::comparator>;

  set impl_;
};

}

#endif
