#include <sanguis/entity_id.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <sanguis/server/world/entity_map.hpp>
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::world::entity_map::entity_map()
:
	impl_()
{
}

sanguis::server::world::entity_map::~entity_map()
{
	for(
		auto element : impl_
	)
		element.second->destroy();
}

sanguis::server::world::entity_map::insert_return_type const
sanguis::server::world::entity_map::insert(
	sanguis::entity_id const _id,
	sanguis::server::entities::unique_ptr &&_entity
)
{
	return
		fcppt::container::ptr::insert_unique_ptr_map(
			impl_,
			_id,
			std::move(
				_entity
			)
		);
}

sanguis::server::world::entity_map::iterator
sanguis::server::world::entity_map::begin()
{
	return
		impl_.begin();
}

sanguis::server::world::entity_map::iterator
sanguis::server::world::entity_map::end()
{
	return
		impl_.end();
}

sanguis::server::world::entity_map::iterator
sanguis::server::world::entity_map::find(
	sanguis::entity_id const _id
)
{
	return
		impl_.find(
			_id
		);
}

sanguis::server::world::entity_map::const_iterator
sanguis::server::world::entity_map::find(
	sanguis::entity_id const _id
) const
{
	return
		impl_.find(
			_id
		);
}

void
sanguis::server::world::entity_map::erase(
	iterator const _it
)
{
	_it->second->destroy();

	impl_.erase(
		_it
	);
}

sanguis::server::entities::unique_ptr
sanguis::server::world::entity_map::release(
	iterator const _it
)
{
	return
		sanguis::server::entities::unique_ptr(
			impl_.release(
				_it
			).release()
		);
}
