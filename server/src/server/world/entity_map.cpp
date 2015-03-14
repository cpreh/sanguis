#include <sanguis/entity_id.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/entities/with_id_unique_ptr.hpp>
#include <sanguis/server/world/entity_map.hpp>
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
	// FIXME: Do we want this here?
	/*
	for(
		auto &element
		:
		impl_
	)
		element.second->remove_from_world();*/
}

sanguis::server::world::entity_map::insert_return_type const
sanguis::server::world::entity_map::insert(
	sanguis::entity_id const _id,
	sanguis::server::entities::with_id_unique_ptr &&_entity
)
{
	return
		impl_.insert(
			std::make_pair(
				_id,
				std::move(
					_entity
				)
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
	// FIXME
	//_it->second->remove_from_world();

	impl_.erase(
		_it
	);
}

sanguis::server::entities::with_id_unique_ptr
sanguis::server::world::entity_map::release(
	iterator const _it
)
{
	sanguis::server::entities::with_id_unique_ptr result(
		std::move(
			_it->second
		)
	);

	impl_.erase(
		_it
	);

	return
		std::move(
			result
		);
}
