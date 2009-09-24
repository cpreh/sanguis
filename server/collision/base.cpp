#include "base.hpp"
#include "satellite.hpp"
#include "create_parameters.hpp"
#include "global_groups.hpp"
#include <sge/collision/world.hpp>
#include <sge/collision/body.hpp>
#include <sge/math/vector/basic_impl.hpp>
#include <sge/math/vector/construct.hpp>
#include <sge/math/vector/narrow_cast.hpp>
#include <sge/make_auto_ptr.hpp>
#include <boost/logic/tribool.hpp>
#include <boost/tr1/functional.hpp>
#include <boost/foreach.hpp>

sanguis::server::collision::base::base()
:
	body_()
{}

void
sanguis::server::collision::base::body_pos(
	pos_type const &pos_
)
{
	body_->position(
		sge::math::vector::construct(
			pos_,
			static_cast<
				space_unit
			>(0)
		)
	);
}

sanguis::server::pos_type const
sanguis::server::collision::base::body_pos() const
{
	return sge::math::vector::narrow_cast<
		pos_type
	>(
		body_->position()
	);
}

void
sanguis::server::collision::base::body_speed(
	pos_type const &speed_
)
{
	body_->linear_velocity(
		sge::math::vector::construct(
			speed_,
			static_cast<
				space_unit
			>(0)
		)
	);
}

sanguis::server::pos_type const
sanguis::server::collision::base::body_speed() const
{
	return sge::math::vector::narrow_cast<
		pos_type
	>(
		body_->linear_velocity()
	);
}

void
sanguis::server::collision::base::recreate(
	sge::collision::world_ptr const world_,
	global_groups const &global_groups_,
	create_parameters const &create_param_
)
{
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
			recreate_shapes(
				world_
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
		group_vector::const_reference group_,
		collision_groups()
	)
		global_groups_.add_to_group(
			body_,
			group_
		);
}

void
sanguis::server::collision::base::destroy()
{
	on_destroy();

	body_.reset();
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
sanguis::server::collision::base::on_destroy()
{}
