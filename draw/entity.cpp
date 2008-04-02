#include "entity.hpp"
	
sanguis::draw::entity::entity(const entity_id id_)
: id_(id_)
{}

sanguis::entity_id sanguis::draw::entity::id() const
{
	return id_;
}

void sanguis::draw::entity::health(sge::space_unit)
{}

void sanguis::draw::entity::max_health(sge::space_unit)
{}
