#include "entity.hpp"
#include <sge/math/vec_dim.hpp>

sanguis::server::entity::entity(const entity_id id_)
: id_(id_)
{}

sanguis::entity_id sanguis::server::entity::id() const
{
	return id_;
}

sanguis::messages::pos_type sanguis::server::entity::center() const
{
	return pos() + dim()/static_cast<messages::space_unit>(2);
}

sanguis::server::entity::~entity()
{}
