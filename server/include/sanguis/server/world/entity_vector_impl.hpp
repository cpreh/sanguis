#ifndef SANGUIS_SERVER_WORLD_ENTITY_VECTOR_IMPL_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_ENTITY_VECTOR_IMPL_HPP_INCLUDED

#include <sanguis/server/world/entity_vector.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


template<
	typename Type
>
sanguis::server::world::entity_vector<
	Type
>::entity_vector()
:
	impl_()
{
}

template<
	typename Type
>
sanguis::server::world::entity_vector<
	Type
>::~entity_vector()
{
	// FIXME
/*
	for(
		auto &entity
		:
		impl_
	)
		entity->remove_from_world();*/
}

template<
	typename Type
>
void
sanguis::server::world::entity_vector<
	Type
>::push_back(
	entity_unique_ptr &&_entity
)
{
	impl_.push_back(
		std::move(
			_entity
		)
	);
}

template<
	typename Type
>
void
sanguis::server::world::entity_vector<
	Type
>::pop_back()
{
	impl_.pop_back();
}

template<
	typename Type
>
Type &
sanguis::server::world::entity_vector<
	Type
>::back()
{
	return
		*impl_.back();
}

template<
	typename Type
>
typename
sanguis::server::world::entity_vector<
	Type
>::iterator
sanguis::server::world::entity_vector<
	Type
>::begin()
{
	return
		impl_.begin();
}

template<
	typename Type
>
typename
sanguis::server::world::entity_vector<
	Type
>::iterator
sanguis::server::world::entity_vector<
	Type
>::end()
{
	return
		impl_.end();
}

template<
	typename Type
>
typename
sanguis::server::world::entity_vector<
	Type
>::iterator
sanguis::server::world::entity_vector<
	Type
>::erase(
	iterator const _it
)
{
	// FIXME
	//(*_it)->remove_from_world();

	return
		impl_.erase(
			_it
		);
}

#endif
