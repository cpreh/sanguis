#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/server/angle.hpp>
#include <sanguis/server/direction.hpp>
#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/entities/projectiles/simple_bullet.hpp>
#include <sanguis/server/environment/insert_no_result.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/weapons/base_cooldown.hpp>
#include <sanguis/server/weapons/cast_point.hpp>
#include <sanguis/server/weapons/damage.hpp>
#include <sanguis/server/weapons/delayed_attack.hpp>
#include <sanguis/server/weapons/magazine_size.hpp>
#include <sanguis/server/weapons/range.hpp>
#include <sanguis/server/weapons/reload_time.hpp>
#include <sanguis/server/weapons/shotgun.hpp>
#include <sanguis/server/weapons/unlimited_magazine_count.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/random/variate.hpp>
#include <fcppt/random/distribution/basic.hpp>
#include <fcppt/random/distribution/parameters/normal.hpp>


sanguis::server::weapons::shotgun::shotgun(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
	sanguis::weapon_type const _type,
	sanguis::server::weapons::base_cooldown const _base_cooldown,
	sanguis::server::weapons::cast_point const _cast_point,
	sanguis::server::weapons::shotgun::spread_radius const _spread_radius,
	sanguis::server::weapons::shotgun::shells const _shells,
	sanguis::server::weapons::damage const _damage,
	sanguis::server::weapons::magazine_size const _magazine_size,
	sanguis::server::weapons::reload_time const _reload_time,
	sanguis::server::weapons::range const _range
)
:
	sanguis::server::weapons::weapon(
		_diff_clock,
		_type,
		_range,
		_magazine_size,
		sanguis::server::weapons::unlimited_magazine_count,
		_base_cooldown,
		_cast_point,
		_reload_time
	),
	random_generator_(
		_random_generator
	),
	spread_radius_(
		_spread_radius
	),
	shells_(
		_shells
	),
	damage_(
		_damage
	)
{
}

sanguis::server::weapons::shotgun::~shotgun()
{
}

void
sanguis::server::weapons::shotgun::do_attack(
	sanguis::server::weapons::delayed_attack const &_attack
)
{
	typedef fcppt::random::distribution::basic<
		fcppt::random::distribution::parameters::normal<
			sanguis::server::space_unit
		>
	> angle_distribution;

	fcppt::random::variate<
		sanguis::random_generator,
		angle_distribution
	> angle_rng(
		random_generator_,
		angle_distribution(
			angle_distribution::param_type::mean(
				_attack.angle().get()
			),
			angle_distribution::param_type::stddev(
				spread_radius_.get()
			)
		)
	);

	for(
		sanguis::server::weapons::shotgun::shells::value_type index(
			0u
		);
		index < shells_.get();
		++index
	)
	{
		sanguis::server::angle const angle(
			angle_rng()
		);

		sanguis::server::environment::insert_no_result(
			_attack.environment(),
			fcppt::make_unique_ptr<
				sanguis::server::entities::projectiles::simple_bullet
			>(
				this->diff_clock(),
				_attack.environment().load_context(),
				_attack.team(),
				damage_,
				sanguis::server::direction(
					angle.get()
				)
			),
			sanguis::server::entities::insert_parameters(
				_attack.spawn_point(),
				angle
			)
		);
	}
}
