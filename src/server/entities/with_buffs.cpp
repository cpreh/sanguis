#include "with_buffs.hpp"
#include "../buffs/buff.hpp"
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <boost/foreach.hpp>

void
sanguis::server::entities::with_buffs::add_buff(
	buffs::buff &_buff
)
{
	buffs_.push_back(
		_buff
	);
}

void
sanguis::server::entities::with_buffs::claim_buff(
	buffs::unique_ptr _buff
)
{
	fcppt::container::ptr::push_back_unique_ptr(
		owned_buffs_,
		move(
			_buff
		)
	);
}

sanguis::server::entities::with_buffs::with_buffs()
:
	base(),
	buffs_()
{}

sanguis::server::entities::with_buffs::~with_buffs()
{}

void
sanguis::server::entities::with_buffs::on_update(
	sanguis::time_delta const &_time
)
{
	BOOST_FOREACH(
		buffs::list::reference ref,
		buffs_
	)
		ref.update(
			*this,
			_time
		);

	for(
		buff_container::iterator it(
			owned_buffs_.begin()
		);
		it != owned_buffs_.end();
	)
	{
		it->update(
			*this,
			_time
		);

		if(
			it->expired()
		)
			it = owned_buffs_.erase(it);
		else
			++it;
	}
}
