#include <sanguis/server/buffs/buff.hpp>
#include <sanguis/server/buffs/provider.hpp>
#include <sanguis/server/buffs/unique_ptr.hpp>
#include <sanguis/server/entities/with_buffs.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/reference_wrapper_comparison.hpp>
#include <fcppt/reference_wrapper_impl.hpp>
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
		sanguis::server::buffs::provider::buff_map::iterator,
		bool
	>
	ret_type;

	ret_type const ret(
		buffs_.insert(
			std::make_pair(
				fcppt::make_ref(
					_entity
				),
				fcppt::make_ref(
					*_buff
				)
			)
		)
	);

	FCPPT_ASSERT_ERROR(
		ret.second
	);

	_entity.add_buff(
		std::move(
			_buff
		)
	);
}

void
sanguis::server::buffs::provider::remove(
	sanguis::server::entities::with_buffs &_entity
)
{
	sanguis::server::buffs::provider::buff_map::iterator const it(
		buffs_.find(
			fcppt::make_ref(
				_entity
			)
		)
	);

	FCPPT_ASSERT_ERROR(
		it != buffs_.end()
	);

	_entity.remove_buff(
		it->second.get()
	);

	buffs_.erase(
		it
	);
}
