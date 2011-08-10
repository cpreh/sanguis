#include "spawn.hpp"
#include "../entities/enemies/create.hpp"
#include "../entities/base.hpp"
#include "../entities/insert_parameters.hpp"
#include "../environment/object.hpp"
#include "../angle.hpp"
#include "../center.hpp"
#include "../space_unit.hpp"
#include "../../random.hpp"
#include <fcppt/math/twopi.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/vector/unit_circle.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/tr1/random.hpp>

void
sanguis::server::waves::spawn(
	sanguis::diff_clock const &_diff_clock,
	environment::object &_env,
	environment::load_context &_load_context,
	enemy_type::type const _etype,
	entities::auto_weak_link const _spawn
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

	server::space_unit const
		rand_angle(
			rng()
		),
		radius(
			static_cast<
				space_unit
			>(
				10
			)
		),
		scale(
			static_cast<
				space_unit
			>(
				1.5
			)
		);

	server::angle const angle(
		static_cast<
			space_unit
		>(
			0
		)
	);

	server::center const center(
		scale
		* radius
		* fcppt::math::vector::unit_circle(
			rand_angle
		)
	);

	_env.insert(
		entities::enemies::create(
			_diff_clock,
			_etype,
			_load_context,
			_spawn
		),
		entities::insert_parameters(
			center,
			angle
		)
	);
}
