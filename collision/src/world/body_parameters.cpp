#include <sanguis/collision/center.hpp>
#include <sanguis/collision/log.hpp>
#include <sanguis/collision/optional_mass.hpp>
#include <sanguis/collision/radius.hpp>
#include <sanguis/collision/speed.hpp>
#include <sanguis/collision/world/body_base_fwd.hpp>
#include <sanguis/collision/world/body_group.hpp>
#include <sanguis/collision/world/body_parameters.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/log/object_fwd.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::collision::world::body_parameters::body_parameters(
	sanguis::collision::log const &_log,
	sanguis::collision::center _center,
	sanguis::collision::speed _speed,
	sanguis::collision::radius _radius,
	sanguis::collision::optional_mass _mass,
	sanguis::collision::world::body_group const _collision_group,
	fcppt::reference<
		sanguis::collision::world::body_base
	> const _body_base
)
:
	log_{
		_log.body_log()
	},
	center_(
		std::move(
			_center
		)
	),
	speed_(
		std::move(
			_speed
		)
	),
	radius_(
		std::move(
			_radius
		)
	),
	mass_(
		std::move(
			_mass
		)
	),
	collision_group_(
		_collision_group
	),
	body_base_(
		_body_base
	)
{
}

fcppt::log::object &
sanguis::collision::world::body_parameters::log() const
{
	return
		log_.get();
}

sanguis::collision::center
sanguis::collision::world::body_parameters::center() const
{
	return
		center_;
}

sanguis::collision::speed
sanguis::collision::world::body_parameters::speed() const
{
	return
		speed_;
}

sanguis::collision::radius
sanguis::collision::world::body_parameters::radius() const
{
	return
		radius_;
}

sanguis::collision::optional_mass
sanguis::collision::world::body_parameters::mass() const
{
	return
		mass_;
}

sanguis::collision::world::body_group
sanguis::collision::world::body_parameters::collision_group() const
{
	return
		collision_group_;
}

sanguis::collision::world::body_base &
sanguis::collision::world::body_parameters::body_base() const
{
	return
		body_base_.get();
}
