#include <sanguis/server/buffs/buff.hpp>
#include <sanguis/server/buffs/unique_ptr.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/with_buffs.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_wrapper_comparison.hpp>
#include <fcppt/reference_wrapper_impl.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


void
sanguis::server::entities::with_buffs::add_buff(
	sanguis::server::buffs::buff &_buff
)
{
	_buff.add(
		*this
	);

	FCPPT_ASSERT_ERROR(
		buffs_.insert(
			fcppt::make_ref(
				_buff
			)
		).second
	);
}

void
sanguis::server::entities::with_buffs::remove_buff(
	sanguis::server::buffs::buff &_buff
)
{
	_buff.remove(
		*this
	);

	FCPPT_ASSERT_ERROR(
		buffs_.erase(
			fcppt::make_ref(
				_buff
			)
		)
		==
		1u
	);
}

void
sanguis::server::entities::with_buffs::claim_buff(
	sanguis::server::buffs::unique_ptr &&_buff
)
{
	FCPPT_ASSERT_ERROR(
		buffs_.erase(
			fcppt::make_ref(
				*_buff
			)
		)
		==
		1u
	);

	fcppt::container::ptr::push_back_unique_ptr(
		owned_buffs_,
		std::move(
			_buff
		)
	);
}

sanguis::server::entities::with_buffs::with_buffs()
:
	sanguis::server::entities::base(),
	buffs_(),
	owned_buffs_()
{
}

sanguis::server::entities::with_buffs::~with_buffs()
{
	FCPPT_ASSERT_ERROR(
		buffs_.empty()
	);
}

void
sanguis::server::entities::with_buffs::update()
{
	for(
		auto &buff
		:
		buffs_
	)
		buff.get().update(
			*this
		);

	for(
		buff_container::iterator it(
			owned_buffs_.begin()
		);
		it != owned_buffs_.end();
	)
	{
		it->update(
			*this
		);

		if(
			it->expired()
		)
		{
			it->remove(
				*this
			);

			it =
				owned_buffs_.erase(
					it
				);
		}
		else
			++it;
	}
}
