#include <sanguis/server/buffs/provider.hpp>
#include <sanguis/server/buffs/buff.hpp>
#include <sanguis/server/entities/with_buffs.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

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

	FCPPT_ASSERT_ERROR(
		ret.second
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

	FCPPT_ASSERT_ERROR(
		it != buffs_.end()
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
