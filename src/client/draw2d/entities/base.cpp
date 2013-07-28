#include <sanguis/client/draw2d/entities/base.hpp>


sanguis::client::draw2d::entities::base::base()
:
	removed_(
		false
	)
{
}

void
sanguis::client::draw2d::entities::base::decay()
{
	this->on_decay();
}

bool
sanguis::client::draw2d::entities::base::may_be_removed() const
{
	return
		removed_
		||
		this->is_decayed();
}

sanguis::client::draw2d::entities::base::~base()
{
}

bool
sanguis::client::draw2d::entities::base::is_decayed() const
{
	return false;
}

void
sanguis::client::draw2d::entities::base::on_decay()
{
	removed_ = true;
}
