#include <sanguis/client/draw2d/entities/base.hpp>


sanguis::client::draw2d::entities::base::base()
{
}

void
sanguis::client::draw2d::entities::base::die()
{
	this->on_die();
}

bool
sanguis::client::draw2d::entities::base::may_be_removed() const
{
	return
		this->is_decayed();
}

sanguis::client::draw2d::entities::base::~base()
{
}
