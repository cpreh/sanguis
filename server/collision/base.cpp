#include "base.hpp"
#include <boost/logic/tribool.hpp>

sanguis::server::collision::base::base(
	sge::collision::objets::base_ptr const base_
)
:
	base_(base_)
{}

sge::collision::objects::base_ptr const
sanguis::server::collision::base::collision_object()
{
	return base_;
}

sge::collision::objects::const_base_ptr const
sanguis::server::collision::base::collision_object() const
{
	return base_;
}

sanguis::server::collision::base::~base()
{}

boost::logic::tribool const
sanguis::server::collision::base::can_collide_with(
	collision::base const &
) const
{
	return boost::logic::indeterminate;
}

void
sanguis::server::collision::base::collision(
	collision::base &
)
{
}
