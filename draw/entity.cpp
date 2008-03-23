#include "entity.hpp"
	
sanguis::draw::entity::entity(const entity_id id_)
: id_(id_)
{}

sanguis::entity_id sanguis::draw::entity::id() const
{
	return id_;
}
