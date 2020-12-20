#include <sanguis/server/angle.hpp>
#include <sanguis/server/environment/object_fwd.hpp>
#include <sanguis/server/environment/object_ref.hpp>
#include <sanguis/server/weapons/attack.hpp>
#include <sanguis/server/weapons/target.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::weapons::attack::attack(
	sanguis::server::angle const _angle,
	sanguis::server::environment::object_ref const _environment,
	sanguis::server::weapons::target _target
)
:
	angle_(
		_angle
	),
	environment_(
		_environment
	),
	target_(
		std::move(
			_target
		)
	)
{
}

sanguis::server::angle
sanguis::server::weapons::attack::angle() const
{
	return
		angle_;
}

sanguis::server::environment::object &
sanguis::server::weapons::attack::environment() const
{
	return
		environment_.get();
}

sanguis::server::weapons::target const &
sanguis::server::weapons::attack::target() const
{
	return
		target_;
}
