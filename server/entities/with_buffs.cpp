#include "with_buffs.hpp"
#include "../buffs/buff.hpp"
#include <boost/foreach.hpp>

void
sanguis::server::entities::with_buffs::add_buff(
	buffs::buff &buff_
)
{
	buffs_.push_back(
		buff_
	);
}

void
sanguis::server::entities::with_buffs::claim_buff(
	buffs::auto_ptr buff_
)
{
	owned_buffs_.push_back(
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
	BOOST_FOREACH(
		buffs::list::reference ref,
		buffs_
	)
		ref.update(
			*this,
			time
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
			time
		);

		if(
			it->expired()
		)
			it = owned_buffs_.erase(it);
		else
			++it;
	}
}
