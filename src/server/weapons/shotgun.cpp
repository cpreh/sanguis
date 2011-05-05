#include "shotgun.hpp"
#include "delayed_attack.hpp"
#include "unlimited_magazine_count.hpp"
#include "../entities/base.hpp"
#include "../entities/insert_parameters.hpp"
#include "../entities/projectiles/simple_bullet.hpp"
#include "../environment/object.hpp"
#include "../../random.hpp"
#include <fcppt/tr1/random.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>

sanguis::server::weapons::shotgun::shotgun(
	weapon_type::type const _type,
	weapons::base_cooldown const _base_cooldown,
	space_unit const _spread_radius,
	unsigned const _shells,
	weapons::damage const _damage,
	weapons::magazine_size const _magazine_size,
	weapons::reload_time const _reload_time
)
:
	weapon(
		_type,
		weapons::range(20), // FIXME
		_magazine_size,
		unlimited_magazine_count,
		_base_cooldown,
		weapons::cast_point(
			0.5f
		), // FIXME
		_reload_time
	),
	spread_radius_(_spread_radius),
	shells_(_shells),
	damage_(_damage)
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
	typedef std::tr1::normal_distribution<
		space_unit
	> normal_distribution_su;

	typedef std::tr1::variate_generator<
		rand_gen_type,
		normal_distribution_su
	> rng_type;

	rng_type rng(
		// TODO: save the randgen!
		create_seeded_randgen(),
		normal_distribution_su(
			_attack.angle().get(), // mean value
			spread_radius_ // sigma
		)
	);

	for(
		unsigned i = 0;
		i < shells_;
		++i
	)
	{
		server::angle const angle(
			rng()
		);

		_attack.environment().insert(
			entities::unique_ptr(
				fcppt::make_unique_ptr<
					entities::projectiles::simple_bullet
				>(
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
