#include <sanguis/server/buffs/buff.hpp>
#include <sanguis/server/buffs/stack.hpp>
#include <sanguis/server/buffs/unique_ptr.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/assert/pre.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::buffs::stack::stack()
:
	impl_()
{
}

sanguis::server::buffs::stack::stack(
	stack &&
)
= default;

sanguis::server::buffs::stack &
sanguis::server::buffs::stack::operator=(
	stack &&
)
= default;

sanguis::server::buffs::stack::~stack()
{
}

void
sanguis::server::buffs::stack::insert(
	sanguis::server::buffs::unique_ptr &&_buff
)
{
	impl_.insert(
		std::move(
			_buff
		)
	);
}

void
sanguis::server::buffs::stack::erase(
	sanguis::server::buffs::buff const &_buff
)
{
	// TODO: With C++14 we can do a proper lookup here
	// TODO: Add a find_opt version to fcppt that returns an iterator
	set::iterator const result(
		std::find_if(
			impl_.begin(),
			impl_.end(),
			[
				&_buff
			](
				sanguis::server::buffs::unique_ptr const &_element
			)
			{
				return
					_element.get()
					==
					&_buff;
			}
		)
	);

	FCPPT_ASSERT_ERROR(
		result
		!=
		impl_.end()
	);

	impl_.erase(
		result
	);
}

bool
sanguis::server::buffs::stack::empty() const
{
	return
		impl_.empty();
}

sanguis::server::buffs::buff &
sanguis::server::buffs::stack::highest_buff()
{
	FCPPT_ASSERT_PRE(
		!this->empty()
	);

	return
		**impl_.begin();
}

sanguis::server::buffs::buff const &
sanguis::server::buffs::stack::highest_buff() const
{
	FCPPT_ASSERT_PRE(
		!this->empty()
	);

	return
		**impl_.begin();
}
