#include "object.hpp"
#include "../../entities/base.hpp"

sanguis::server::world::deferred_add::object::object(
	entities::auto_ptr entity_,
	entities::insert_parameters const &insert_parameters_
)
:
	entity_(entity_),
	insert_parameters_(insert_parameters_)
{}
	
sanguis::server::world::deferred_add::object::~object()
{}

sanguis::server::entities::base &
sanguis::server::world::deferred_add::object::entity()
{
	return *entity_;
}

sanguis::server::entities::auto_ptr
sanguis::server::world::deferred_add::object::release_entity()
{
	return entity_;	
}

sanguis::server::entities::insert_parameters const &
sanguis::server::world::deferred_add::object::insert_parameters() const
{
	return insert_parameters_;
}

