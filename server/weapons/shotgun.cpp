#include "shotgun.hpp"
#include "delayed_attack.hpp"
#include "../damage_types.hpp"
#include "../entities/entity.hpp"
#include "../entities/projectiles/simple_bullet.hpp"
#include "../../random.hpp"
#include <boost/tr1/random.hpp>

sanguis::server::weapons::shotgun::shotgun(
	const environment &env,
	const weapon_type::type type_,
	const time_type base_cooldown,
	const messages::space_unit spread_radius,
	const unsigned shells,
	const messages::space_unit damage)
: weapon(
	env,
	type_,
	1000, // FIXME
	base_cooldown,
	static_cast<time_type>(
		0.5)), // FIXME
  spread_radius(spread_radius),
  shells(shells),
  damage(damage)
{}

void sanguis::server::weapons::shotgun::do_attack(
	delayed_attack const &a)
{
	typedef std::tr1::normal_distribution<
		messages::space_unit
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
		));

	for(unsigned i = 0; i < shells; ++i)
		insert(
			entities::auto_ptr(
				new entities::projectiles::simple_bullet(
					get_environment(),
					damage::list(damage::normal = messages::mu(1)),
					a.spawn_point(),
					rng(),
					a.team(),
					damage)));
}
