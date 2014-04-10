#include <sanguis/client/draw2d/center.hpp>
#include <sanguis/client/draw2d/radius.hpp>
#include <sanguis/client/draw2d/entities/name.hpp>
#include <sanguis/client/draw2d/scene/shown_name.hpp>


sanguis::client::draw2d::scene::shown_name::shown_name(
	sanguis::client::draw2d::center const _center,
	sanguis::client::draw2d::radius const _radius,
	sanguis::client::draw2d::entities::name const &_name
)
:
	center_(
		_center
	),
	radius_(
		_radius
	),
	name_(
		_name
	)
{
}

sanguis::client::draw2d::center const
sanguis::client::draw2d::scene::shown_name::center() const
{
	return
		center_;
}

sanguis::client::draw2d::radius const
sanguis::client::draw2d::scene::shown_name::radius() const
{
	return
		radius_;
}

sanguis::client::draw2d::entities::name const &
sanguis::client::draw2d::scene::shown_name::name() const
{
	return
		name_;
}
