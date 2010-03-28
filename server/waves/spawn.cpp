#include "spawn.hpp"
#include "../entities/enemies/factory.hpp"
#include "../entities/base.hpp"
#include "../entities/insert_parameters.hpp"
#include "../environment/object.hpp"
#include "../../random.hpp"
#include "../../angle_to_vector.hpp"
#include <fcppt/math/twopi.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/tr1/random.hpp>

void
sanguis::server::waves::spawn(
	environment::object_ptr const env,
	environment::load_context_ptr const load_context,
	enemy_type::type const etype,
	entities::auto_weak_link const spawn
)
{
	// TODO: put this randomizer somewhere else!
	
	typedef std::tr1::uniform_real<
		space_unit
	> uniform_su;

	typedef std::tr1::variate_generator<
		rand_gen_type,
		uniform_su
	> rng_type;

	static rng_type rng(
		create_seeded_randgen(),
		uniform_su(
			static_cast<space_unit>(0),
			fcppt::math::twopi<space_unit>()
		)
	);

	space_unit const
		rand_angle(rng()),
		radius(
			static_cast<
				space_unit
			>(
				500
			)
		),
		scale(static_cast<space_unit>(1.5)),
		angle(static_cast<space_unit>(0)
	);
	
	pos_type const
		center(
			scale * radius * angle_to_vector(rand_angle)
		),
		pos(
			center
		);

	env->insert(
		entities::enemies::create(
			etype,
			load_context,
			spawn
		),
		entities::insert_parameters(
			pos,
			angle
		)
	);
}
