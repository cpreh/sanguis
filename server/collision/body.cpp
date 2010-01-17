#include "body.hpp"
#include "create_parameters.hpp"
#include "global_groups.hpp"
#include <sge/collision/world.hpp>
#include <sge/collision/body.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/construct.hpp>
#include <fcppt/math/vector/narrow_cast.hpp>
#include <fcppt/algorithm/append.hpp>
#include <boost/foreach.hpp>

sanguis::server::collision::body::body()
:
	body_(),
	shapes_()
{}

void
sanguis::server::collision::body::body_pos(
	pos_type const &pos_
)
{
	body_->position(
		fcppt::math::vector::construct(
			pos_,
			static_cast<
				space_unit
			>(0)
		)
	);
}

sanguis::server::pos_type const
sanguis::server::collision::body::body_pos() const
{
	return fcppt::math::vector::narrow_cast<
		pos_type
	>(
		body_->position()
	);
}

void
sanguis::server::collision::body::body_speed(
	pos_type const &speed_
)
{
	body_->linear_velocity(
		fcppt::math::vector::construct(
			speed_,
			static_cast<
				space_unit
			>(0)
		)
	);
}

sanguis::server::pos_type const
sanguis::server::collision::body::body_speed() const
{
	return fcppt::math::vector::narrow_cast<
		pos_type
	>(
		body_->linear_velocity()
	);
}

void
sanguis::server::collision::body::add_shapes(
	sge::collision::shapes::container const &new_shapes_
)
{
	fcppt::algorithm::append(
		shapes_,
		new_shapes_
	);

	BOOST_FOREACH(
		sge::collision::shapes::container::const_reference ref,
		new_shapes_
	)
		body_->add_shape(
			ref
		);
}

void
sanguis::server::collision::body::recreate(
	sge::collision::world_ptr const world_,
	global_groups const &global_groups_,
	create_parameters const &create_param_
)
{
	sge::collision::shapes::container const new_shapes_(
		recreate_shapes(
			world_,
			global_groups_
		)
	);

	shapes_.clear();

	body_ =
		world_->create_body(
			shapes_,
			fcppt::math::vector::construct(
				create_param_.center(),
				static_cast<
					space_unit
				>(0)
			),
			fcppt::math::vector::construct(
				create_param_.speed(),
				static_cast<
					space_unit
				>(0)
			)
		);
	
	add_shapes(
		new_shapes_
	);
}

void
sanguis::server::collision::body::destroy()
{
	on_destroy();

	shapes_.clear();

	body_.reset();
}

sanguis::server::collision::body::~body()
{}

void
sanguis::server::collision::body::on_destroy()
{}
