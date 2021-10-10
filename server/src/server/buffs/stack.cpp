#include <sanguis/exception.hpp>
#include <sanguis/server/buffs/buff.hpp>
#include <sanguis/server/buffs/stack.hpp>
#include <sanguis/server/buffs/unique_ptr.hpp>
#include <fcppt/text.hpp>
#include <fcppt/assert/optional_error.hpp>
#include <fcppt/container/find_opt_iterator.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

sanguis::server::buffs::stack::stack() : impl_() {}

sanguis::server::buffs::stack::stack(stack &&) noexcept = default;

sanguis::server::buffs::stack &
sanguis::server::buffs::stack::operator=(stack &&) noexcept = default;

sanguis::server::buffs::stack::~stack() = default;

void sanguis::server::buffs::stack::insert(sanguis::server::buffs::unique_ptr &&_buff)
{
  impl_.insert(std::move(_buff));
}

void sanguis::server::buffs::stack::erase(sanguis::server::buffs::buff const &_buff)
{
  impl_.erase(FCPPT_ASSERT_OPTIONAL_ERROR(fcppt::container::find_opt_iterator(impl_, _buff)));
}

bool sanguis::server::buffs::stack::empty() const { return impl_.empty(); }

sanguis::server::buffs::buff &sanguis::server::buffs::stack::highest_buff()
{
  if (this->empty())
  {
    throw sanguis::exception{FCPPT_TEXT("stack::highest_buff: stack is empty")};
  }

  return **impl_.begin();
}

sanguis::server::buffs::buff const &sanguis::server::buffs::stack::highest_buff() const
{
  if (this->empty())
  {
    throw sanguis::exception{FCPPT_TEXT("stack::highest_buff: stack is empty")};
  }

  return **impl_.begin();
}
