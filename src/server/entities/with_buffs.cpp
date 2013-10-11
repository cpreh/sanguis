#include <sanguis/server/buffs/buff.hpp>
#include <sanguis/server/buffs/unique_ptr.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/with_buffs.hpp>
#include <fcppt/algorithm/ptr_container_erase.hpp>
#include <fcppt/assert/error.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


void
sanguis::server::entities::with_buffs::add_buff(
	sanguis::server::buffs::unique_ptr &&_buff
)
{
	_buff->add(
		*this
	);

	fcppt::container::ptr::push_back_unique_ptr(
		buffs_,
		std::move(
			_buff
		)
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
		fcppt::algorithm::ptr_container_erase(
			buffs_,
			&_buff
		)
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
		elem.update(
			*this
		);
}
