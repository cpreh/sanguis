#include "shotgun.hpp"
#include "delayed_attack.hpp"
#include "../entities/entity.hpp"
#include "../entities/projectiles/simple_bullet.hpp"
#include "../../random.hpp"
#include <boost/tr1/random.hpp>

sanguis::server::weapons::shotgun::shotgun(
	server::environment const &env,
	weapon_type::type const type_,
	time_type const base_cooldown,
	space_unit const spread_radius,
	unsigned const shells,
	space_unit const damage,
	unsigned const magazine_size,
	time_type const reload_time)
:
	weapon(
		env,
		type_,
		weapons::range(1000), // FIXME
		magazine_size,
		unlimited_magazine,
		base_cooldown,
		static_cast<
			time_type
		>(
			0.5
		), // FIXME
		reload_time
	),
	spread_radius(spread_radius),
	shells(shells),
	damage(damage)
{}

void sanguis::server::weapons::shotgun::do_attack(
	delayed_attack const &a)
{
	typedef std::tr1::normal_distribution<
		space_unit
	> normal_distribution_su;

	typedef std::tr1::variate_generator<
		rand_gen_type,
		normal_distribution_su
	> rng_type;

	rng_type rng(
		create_seeded_randgen(),
		normal_distribution_su(
			a.angle(), // mean value
			spread_radius // sigma
		)
	);

	for(unsigned i = 0; i < shells; ++i)
		insert(
			entities::auto_ptr(
				new entities::projectiles::simple_bullet(
					environment(),
					a.spawn_point(),
					rng(),
					a.team(),
					damage
				)
			)
		);
}
