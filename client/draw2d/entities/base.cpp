#include "base.hpp"

sanguis::client::draw2d::entities::base::base()
:
	may_be_removed_(false)
{}

void
sanguis::client::draw2d::entities::base::decay()
{}

bool
sanguis::client::draw2d::entities::base::may_be_removed() const
{
	return may_be_removed_;
}

void
sanguis::client::draw2d::entities::base::on_remove()
{}

sanguis::client::draw2d::entities::base::~base()
{}
