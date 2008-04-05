#include "entity.hpp"

sanguis::server::entity::entity(const entity_id id_)
: id_(id_)
{}

sanguis::entity_id sanguis::server::entity::id() const
{
	return id_;
}

sanguis::server::entity::~entity()
{}
