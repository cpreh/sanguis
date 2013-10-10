#include <sanguis/server/buffs/buff.hpp>
#include <sanguis/server/buffs/map.hpp>
#include <sanguis/server/buffs/provider.hpp>
#include <sanguis/server/buffs/unique_ptr.hpp>
#include <sanguis/server/entities/with_buffs.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::buffs::provider::provider()
:
	buffs_()
{
}

sanguis::server::buffs::provider::~provider()
{
	FCPPT_ASSERT_ERROR(
		buffs_.empty()
	);
}

void
sanguis::server::buffs::provider::add(
	sanguis::server::entities::with_buffs &_entity,
	sanguis::server::buffs::unique_ptr &&_buff
)
{
	typedef
	std::pair<
		sanguis::server::buffs::map::iterator,
		bool
	>
	ret_type;

	ret_type const ret(
		fcppt::container::ptr::insert_unique_ptr_map(
			buffs_,
			&_entity,
			std::move(
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
	sanguis::server::entities::with_buffs &_entity
)
{
	sanguis::server::buffs::map::iterator const it(
		buffs_.find(
			&_entity
		)
	);

	FCPPT_ASSERT_ERROR(
		it != buffs_.end()
	);

	sanguis::server::buffs::map::auto_type reclaimed(
		buffs_.release(
			it
		)
	);

	reclaimed->owner_lost();

	if(
		reclaimed->expired()
	)
		_entity.remove_buff(
			*reclaimed
		);
	else
		_entity.claim_buff(
			sanguis::server::buffs::unique_ptr(
				reclaimed.release()
			)
		);
}
