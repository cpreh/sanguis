#include "provider.hpp"
#include "buff.hpp"
#include "../entities/with_buffs.hpp"
#include "../../exception.hpp"
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>
#include <fcppt/text.hpp>
#include <utility>

sanguis::server::buffs::provider::provider()
:
	buffs_()
{}

sanguis::server::buffs::provider::~provider()
{}

void
sanguis::server::buffs::provider::add(
	entities::with_buffs &_entity,
	unique_ptr _buff
)
{
	typedef std::pair<
		map::iterator,
		bool
	> ret_type;
	
	ret_type const ret(
		fcppt::container::ptr::insert_unique_ptr_map(
			buffs_,
			_entity.id(),
			move(
				_buff
			)
		)
	);

	if(
		!ret.second
	)
		throw exception(
			FCPPT_TEXT("Double buff insertion!")
		);
	
	_entity.add_buff(
		*ret.first->second
	);
}

void
sanguis::server::buffs::provider::remove(
	entities::with_buffs &_entity
)
{
	map::iterator const it(
		buffs_.find(
			_entity.id()
		)
	);

	if(
		it == buffs_.end()
	)
		throw exception(
			FCPPT_TEXT("No buff for an entity!")
		);
	
	map::auto_type reclaimed(
		buffs_.release(
			it
		)
	);

	if(
		!reclaimed->expired()
	)
		_entity.claim_buff(
			buffs::unique_ptr(
				reclaimed.release()
			)
		);
}
