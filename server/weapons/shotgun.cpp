#include "shotgun.hpp"
#include "delayed_attack.hpp"
#include "unlimited_magazine_count.hpp"
#include "../entities/entity.hpp"
#include "../entities/projectiles/simple_bullet.hpp"
#include "../environment/object.hpp"
#include "../../random.hpp"
#include <boost/tr1/random.hpp>

sanguis::server::weapons::shotgun::shotgun(
	server::environment::object_ptr const env,
	weapon_type::type const type_,
	weapons::base_cooldown const base_cooldown_,
	space_unit const spread_radius,
	unsigned const shells,
	weapons::damage const damage_,
	weapons::magazine_size const magazine_size_,
	weapons::reload_time const reload_time_
)
:
	weapon(
		env,
		type_,
		weapons::range(1000), // FIXME
		magazine_size_,
		unlimited_magazine_count,
		base_cooldown_,
		weapons::cast_point(
			0.5f
		), // FIXME
		reload_time_
	),
	spread_radius(spread_radius),
	shells(shells),
	damage_(damage_)
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

	for(
		unsigned i = 0; i < shells; ++i
	)
		environment()->insert(
			entities::auto_ptr(
				new entities::projectiles::simple_bullet(
					environment(),
					a.spawn_point(),
					rng(),
					a.team(),
					damage_
				)
			)
		);
}
