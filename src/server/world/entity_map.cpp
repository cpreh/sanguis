#include "entity_map.hpp"
#include "../entities/base.hpp"
#include <fcppt/container/ptr/insert_unique_ptr_map.hpp>
#include <boost/foreach.hpp>

sanguis::server::world::entity_map::entity_map()
:
	impl_()
{
}

sanguis::server::world::entity_map::~entity_map()
{
	BOOST_FOREACH(
		impl::reference ref,
		impl_
	)
		ref.second->destroy();
}

sanguis::server::world::entity_map::insert_return_type const
sanguis::server::world::entity_map::insert(
	sanguis::entity_id const _id,
	entities::unique_ptr _entity
)
{
	return
		fcppt::container::ptr::insert_unique_ptr_map(
			impl_,
			_id,
			move(
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
		entities::unique_ptr(
			impl_.release(
				_it
			).release()
		);
}
