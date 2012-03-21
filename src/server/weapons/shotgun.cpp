#include <sanguis/duration_second.hpp>
#include <sanguis/random_generator.hpp>
#include <sanguis/server/weapons/shotgun.hpp>
#include <sanguis/server/weapons/delayed_attack.hpp>
#include <sanguis/server/weapons/unlimited_magazine_count.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/entities/projectiles/simple_bullet.hpp>
#include <sanguis/server/environment/object.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>
#include <fcppt/random/variate.hpp>
#include <fcppt/random/distribution/normal.hpp>


sanguis::server::weapons::shotgun::shotgun(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
	weapon_type::type const _type,
	weapons::base_cooldown const _base_cooldown,
	shotgun::spread_radius const _spread_radius,
	shotgun::shells const _shells,
	weapons::damage const _damage,
	weapons::magazine_size const _magazine_size,
	weapons::reload_time const _reload_time
)
:
	weapons::weapon(
		_diff_clock,
		_type,
		weapons::range(
			20.f
		), // FIXME
		_magazine_size,
		unlimited_magazine_count,
		_base_cooldown,
		weapons::cast_point(
			sanguis::duration_second(
				0.5f
			)
		), // FIXME
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
	delayed_attack const &_attack
)
{
	typedef fcppt::random::distribution::normal<
		server::space_unit
	> angle_distribution;

	fcppt::random::variate<
		sanguis::random_generator,
		angle_distribution
	> angle_rng(
		random_generator_,
		angle_distribution(
			angle_distribution::mean(
				_attack.angle().get()
			),
			angle_distribution::sigma(
				spread_radius_.get()
			)
		)
	);

	for(
		shells::value_type index(
			0u
		);
		index < shells_.get();
		++index
	)
	{
		server::angle const angle(
			angle_rng()
		);

		_attack.environment().insert(
			entities::unique_ptr(
				fcppt::make_unique_ptr<
					entities::projectiles::simple_bullet
				>(
					fcppt::cref(
						this->diff_clock()
					),
					fcppt::ref(
						_attack.environment().load_context()
					),
					_attack.team(),
					damage_,
					server::direction(
						angle.get()
					)
				)
			),
			entities::insert_parameters(
				_attack.spawn_point(),
				angle
			)
		);
	}
}
