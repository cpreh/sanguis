#include "base.hpp"
#include <boost/logic/tribool.hpp>

sanguis::server::collision::base::base()
{}

sanguis::server::collision::base::~base()
{}

boost::logic::tribool const
sanguis::server::collision::base::can_collide_with(
	collision::base const &
) const
{
	return boost::logic::indeterminate;
}
