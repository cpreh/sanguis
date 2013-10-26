#include <sanguis/client/draw2d/entities/base.hpp>
#include <sanguis/client/draw2d/entities/name.hpp>
#include <fcppt/string.hpp>


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

sanguis::client::draw2d::entities::name
sanguis::client::draw2d::entities::base::name() const
{
	return
		sanguis::client::draw2d::entities::name(
			fcppt::string()
		);
}

sanguis::client::draw2d::entities::base::~base()
{
}
