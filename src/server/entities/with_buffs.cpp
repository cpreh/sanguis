#include <sanguis/server/buffs/buff.hpp>
#include <sanguis/server/buffs/unique_ptr.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/with_buffs.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <typeindex>
#include <utility>
#include <fcppt/config/external_end.hpp>


void
sanguis::server::entities::with_buffs::add_buff(
	sanguis::server::buffs::unique_ptr &&_buff
)
{
	std::type_index const index(
		typeid(
			*_buff
		)
	);

	buff_map::iterator const it(
		buffs_.find(
			index
		)
	);

	if(
		it == buffs_.end()
	)
	{
		typedef
		std::pair<
			buff_map::iterator,
			bool
		>
		insert_result;

		insert_result const result(
			buffs_.insert(
				std::make_pair(
					index,
					buff_set()
				)
			)
		);

		_buff->add(
			*this
		);

		result.first->second.insert(
			std::move(
				_buff
			)
		);

		return;
	}

	buff_set &set(
		it->second
	);

	FCPPT_ASSERT_ERROR(
		!set.empty()
	);

	(*set.begin())->remove(
		*this
	);

	set.insert(
		std::move(
			_buff
		)
	);

	(*set.begin())->add(
		*this
	);
}

void
sanguis::server::entities::with_buffs::remove_buff(
	sanguis::server::buffs::buff &_buff
)
{
	std::type_index const index(
		typeid(
			_buff
		)
	);

	buff_map::iterator const it(
		buffs_.find(
			index
		)
	);

	FCPPT_ASSERT_ERROR(
		it != buffs_.end()
	);

	buff_set &set(
		it->second
	);

	(*set.begin())->remove(
		*this
	);

	{
		buff_set::iterator const set_it(
			std::find_if(
				set.begin(),
				set.end(),
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
			set_it
			!=
			set.end()
		);

		set.erase(
			set_it
		);
	}

	if(
		set.empty()
	)

		buffs_.erase(
			it
		);
	else
		(*set.begin())->add(
			*this
		);
}

sanguis::server::entities::with_buffs::with_buffs()
:
	sanguis::server::entities::base(),
	buffs_()
{
}

sanguis::server::entities::with_buffs::~with_buffs()
{
}

void
sanguis::server::entities::with_buffs::update()
{
	for(
		auto &elem
		:
		buffs_
	)
		(*elem.second.begin())->update(
			*this
		);
}
