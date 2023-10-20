#ifndef SANGUIS_SERVER_WORLD_INSERT_PAIR_IMPL_HPP_INCLUDED
#define SANGUIS_SERVER_WORLD_INSERT_PAIR_IMPL_HPP_INCLUDED

#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/world/insert_pair_decl.hpp> // IWYU pragma: export
#include <fcppt/unique_ptr_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>

template <typename Type>
sanguis::server::world::insert_pair<Type>::insert_pair(
    unique_ptr &&_entity, sanguis::server::entities::insert_parameters const _insert_parameters)
    : entity_(std::move(_entity)), insert_parameters_(_insert_parameters)
{
}

template <typename Type>
sanguis::server::world::insert_pair<Type>::insert_pair(insert_pair &&) noexcept = default;

template <typename Type>
sanguis::server::world::insert_pair<Type> &
sanguis::server::world::insert_pair<Type>::operator=(insert_pair &&) noexcept = default;

namespace sanguis::server::world
{
template <typename Type>
insert_pair<Type>::~insert_pair() = default;
}

template <typename Type>
typename sanguis::server::world::insert_pair<Type>::unique_ptr &
sanguis::server::world::insert_pair<Type>::entity()
{
  return entity_;
}

template <typename Type>
sanguis::server::entities::insert_parameters const &
sanguis::server::world::insert_pair<Type>::insert_parameters() const
{
  return insert_parameters_;
}

#endif
