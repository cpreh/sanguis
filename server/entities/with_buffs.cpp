#include "with_buffs.hpp"
#include "../buffs/buff.hpp"

void
sanguis::server::entities::with_buffs::add_buff(
	buffs::auto_ptr buff_
)
{
	buffs_.push_back(
		buff_
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
	time_type const time
)
{
	for(
		buff_container::iterator it(buffs_.begin());
		it != buffs_.end();
	)
	{
		it->update(
			*this,
			time
		);

		if(it->expired())
			it = buffs_.erase(it);
		else
			++it;
	}
}
