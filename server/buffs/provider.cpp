#include "provider.hpp"
#include "buff.hpp"
#include "../entities/with_buffs.hpp"
#include "../../exception.hpp"
#include <sge/text.hpp>
#include <utility>

sanguis::server::buffs::provider::provider()
:
	buffs_()
{}

sanguis::server::buffs::provider::~provider()
{}

void
sanguis::server::buffs::provider::add(
	entities::with_buffs &entity_,
	auto_ptr buff_
)
{
	std::pair<
		map::iterator,
		bool
	> const ret(
		buffs_.insert(
			entity_.id(),
			buff_
		)
	);

	if(
		!ret.second
	)
		throw exception(
			SGE_TEXT("Double buff insertion!")
		);
	
	entity_.add_buff(
		*ret.first->second
	);
}

void
sanguis::server::buffs::provider::remove(
	entities::with_buffs &entity_
)
{
	map::iterator const it(
		buffs_.find(
			entity_.id()
		)
	);

	if(
		it == buffs_.end()
	)
		throw exception(
			SGE_TEXT("No buff for an entity!")
		);
	
	map::auto_type reclaimed(
		buffs_.release(
			it
		)
	);

	if(
		!reclaimed->expired()
	)
		entity_.claim_buff(
			auto_ptr(
				reclaimed.release()
			)
		);
}
