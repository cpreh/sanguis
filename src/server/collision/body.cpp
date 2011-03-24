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
	pos_type const &_pos
)
{
	body_->position(
		fcppt::math::vector::construct(
			_pos,
			static_cast<
				space_unit
			>(0)
		)
	);
}

sanguis::server::pos_type const
sanguis::server::collision::body::body_pos() const
{
	return
		fcppt::math::vector::narrow_cast<
			pos_type
		>(
			body_->position()
		);
}

void
sanguis::server::collision::body::body_speed(
	pos_type const &_speed
)
{
	body_->linear_velocity(
		fcppt::math::vector::construct(
			_speed,
			static_cast<
				space_unit
			>(0)
		)
	);
}

sanguis::server::pos_type const
sanguis::server::collision::body::body_speed() const
{
	return
		fcppt::math::vector::narrow_cast<
			pos_type
		>(
			body_->linear_velocity()
		);
}

void
sanguis::server::collision::body::add_shapes(
	sge::collision::shapes::container const &_shapes
)
{
	fcppt::algorithm::append(
		shapes_,
		_shapes
	);

	BOOST_FOREACH(
		sge::collision::shapes::container::const_reference ref,
		_shapes
	)
		body_->add_shape(
			ref
		);
}

void
sanguis::server::collision::body::recreate(
	sge::collision::world_ptr const _world,
	global_groups const &_global_groups,
	create_parameters const &_create_param
)
{
	sge::collision::shapes::container const new_shapes(
		this->recreate_shapes(
			_world,
			_global_groups
		)
	);

	shapes_.clear();

	body_ =
		_world->create_body(
			shapes_,
			fcppt::math::vector::construct(
				_create_param.center(),
				static_cast<
					space_unit
				>(0)
			),
			fcppt::math::vector::construct(
				_create_param.speed(),
				static_cast<
					space_unit
				>(0)
			)
		);
	
	this->add_shapes(
		new_shapes
	);
}

void
sanguis::server::collision::body::destroy()
{
	this->on_destroy();

	shapes_.clear();

	body_.reset();
}

sanguis::server::collision::body::~body()
{}

void
sanguis::server::collision::body::on_destroy()
{}
