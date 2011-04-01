#include "body_base.hpp"
#include <boost/logic/tribool.hpp>

sanguis::server::collision::body_base::body_base()
{
}

sanguis::server::collision::body_base::~body_base()
{
}

boost::logic::tribool const
sanguis::server::collision::body_base::can_collide_with(
	collision::body_base const &
)
{
	return boost::logic::indeterminate;
}

void
sanguis::server::collision::body_base::collision(
	collision::body_base &
)
{
}
