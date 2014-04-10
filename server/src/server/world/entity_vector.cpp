#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <sanguis/server/world/entity_vector.hpp>
#include <fcppt/container/ptr/push_back_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::world::entity_vector::entity_vector()
:
	impl_()
{
}

sanguis::server::world::entity_vector::~entity_vector()
{
	for(
		auto &entity
		:
		impl_
	)
		entity.destroy();
}

void
sanguis::server::world::entity_vector::push_back(
	sanguis::server::entities::unique_ptr &&_entity
)
{
	fcppt::container::ptr::push_back_unique_ptr(
		impl_,
		std::move(
			_entity
		)
	);
}

sanguis::server::entities::base &
sanguis::server::world::entity_vector::back()
{
	return
		impl_.back();
}

sanguis::server::world::entity_vector::iterator
sanguis::server::world::entity_vector::begin()
{
	return
		impl_.begin();
}

sanguis::server::world::entity_vector::iterator
sanguis::server::world::entity_vector::end()
{
	return
		impl_.end();
}

sanguis::server::world::entity_vector::iterator
sanguis::server::world::entity_vector::erase(
	iterator const _it
)
{
	_it->destroy();

	return
		impl_.erase(
			_it
		);
}
