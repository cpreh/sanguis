#include <sanguis/collision/world/created.hpp>
#include <sanguis/server/angle.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>


sanguis::server::entities::insert_parameters::insert_parameters(
	sanguis::server::center const _center,
	sanguis::server::angle const _angle
)
:
	sanguis::server::entities::insert_parameters::insert_parameters(
		_center,
		_angle,
		sanguis::collision::world::created{
			true
		}
	)
{
}

sanguis::server::entities::insert_parameters::insert_parameters(
	sanguis::server::center const _center,
	sanguis::server::angle const _angle,
	sanguis::collision::world::created const _created
)
:
	center_(
		_center
	),
	angle_(
		_angle
	),
	created_{
		_created
	}
{
}

sanguis::server::center const
sanguis::server::entities::insert_parameters::center() const
{
	return
		center_;
}

sanguis::server::angle const
sanguis::server::entities::insert_parameters::angle() const
{
	return
		angle_;
}

sanguis::collision::world::created const
sanguis::server::entities::insert_parameters::created() const
{
	return
		created_;
}
