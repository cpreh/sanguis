#include "entity.hpp"
#include <sge/iostream.hpp>
#include <ostream>
	
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

void sanguis::draw::entity::weapon(weapon_type::type)
{
	sge::clog << SGE_TEXT("warning: entity got a weapon message that can't have a weapon!\n");
}
