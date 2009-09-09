#include "base.hpp"
#include "satellite.hpp"
#include <sge/collision/world.hpp>
#include <sge/math/vector/construct.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <boost/logic/tribool.hpp>

sanguis::server::collision::base::base(
	sge::collision::world_ptr const collision_,
	pos_type const &center,
	pos_type const &speed,
	space_unit const radius)
:
	circle_(
		collision_->create_circle(
			sge::collision::satellite_ptr(
				new satellite(*this)
			),
			sge::math::vector::construct(
				center,
				static_cast<
					space_unit
				>(0)
			),
			sge::math::vector::construct(
				speed,
				static_cast<
					space_unit
				>(0)
			),
			static_cast<sge::collision::unit>(
				radius
			)
		)
	)
{}

/*
sge::collision::objects::circle_ptr const
sanguis::server::collision::base::circle()
{
	return circle_;
}

sge::collision::objects::const_circle_ptr const
sanguis::server::collision::base::circle() const
{
	return circle_;
}
*/

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
	collision::base &)
{
}
