#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/entities/unique_ptr.hpp>
#include <sanguis/server/world/insert_pair.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::world::insert_pair::insert_pair(
	sanguis::server::entities::unique_ptr &&_entity,
	sanguis::server::entities::insert_parameters const &_insert_parameters
)
:
	entity_(
		std::move(
			_entity
		)
	),
	insert_parameters_(
		_insert_parameters
	)
{
}

sanguis::server::world::insert_pair::insert_pair(
	insert_pair &&
) = default;

sanguis::server::world::insert_pair &
sanguis::server::world::insert_pair::operator=(
	insert_pair &&
) = default;

sanguis::server::world::insert_pair::~insert_pair()
{
}

sanguis::server::entities::unique_ptr &
sanguis::server::world::insert_pair::entity()
{
	return
		entity_;
}

sanguis::server::entities::insert_parameters const &
sanguis::server::world::insert_pair::insert_parameters() const
{
	return
		insert_parameters_;
}
