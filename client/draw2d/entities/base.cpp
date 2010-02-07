#include "base.hpp"

sanguis::client::draw2d::entities::base::base()
:
	removed_(false)
{}

void
sanguis::client::draw2d::entities::base::decay()
{
	// decay can be overridden so that is_decayed() can be used
	removed_ = true;
}

void
sanguis::client::draw2d::entities::base::remove()
{
	removed_ = true;
}

void
sanguis::client::draw2d::entities::base::on_remove()
{}

bool
sanguis::client::draw2d::entities::base::may_be_removed() const
{
	return
		removed_
		|| is_decayed();
}

sanguis::client::draw2d::entities::base::~base()
{}

bool
sanguis::client::draw2d::entities::base::is_decayed() const
{
	return false;
}
