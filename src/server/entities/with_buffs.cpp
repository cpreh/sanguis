#include <sanguis/server/buffs/buff.hpp>
#include <sanguis/server/buffs/list.hpp>
#include <sanguis/server/buffs/unique_ptr.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/with_buffs.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


void
sanguis::server::entities::with_buffs::add_buff(
	sanguis::server::buffs::buff &_buff
)
{
	buffs_.push_back(
		_buff
	);
}

void
sanguis::server::entities::with_buffs::claim_buff(
	sanguis::server::buffs::unique_ptr &&_buff
)
{
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
}

void
sanguis::server::entities::with_buffs::update()
{
	for(
		auto &buff : buffs_
	)
		buff.update(
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
			it = owned_buffs_.erase(it);
		else
			++it;
	}
}
