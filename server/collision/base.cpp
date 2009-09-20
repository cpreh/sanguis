#include "base.hpp"
#include "satellite.hpp"
#include "create_parameters.hpp"
#include <sge/collision/world.hpp>
#include <sge/collision/body.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/vector/construct.hpp>
#include <sge/make_auto_ptr.hpp>
#include <boost/logic/tribool.hpp>
#include <boost/tr1/functional.hpp>
#include <boost/foreach.hpp>

sanguis::server::collision::base::base()
:
	body_(),
	shapes_()
{}

sge::collision::body_ptr const
sanguis::server::collision::base::body()
{
	return body_;
}

sge::collision::const_body_ptr const
sanguis::server::collision::base::body() const
{
	return body_;
}

void
sanguis::server::collision::base::recreate(
	sge::collision::world_ptr const world_,
	create_parameters const &create_param_
)
{
	shapes_
		= recreate_shapes(
			world_
		);
	
	body_
		= world_->create_body(
			sge::collision::satellite_ptr(
				sge::make_auto_ptr<
					collision::satellite
				>(
					std::tr1::ref(
						*this
					)
				)
			),
			sge::math::vector::construct(
				create_param_.center(),
				static_cast<
					space_unit
				>(0)
			),
			sge::math::vector::construct(
				create_param_.speed(),
				static_cast<
					space_unit
				>(0)
			)
		);
	
	BOOST_FOREACH(
		shape_vector::const_reference shape_,
		shapes_
	)
		body_->add(
			shape_
		);
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
sanguis::server::collision::base::collision_begin(
	collision::base &
)
{
}

void
sanguis::server::collision::base::collision_end(
	collision::base &
)
{
}
