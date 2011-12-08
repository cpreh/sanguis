#include <sanguis/server/waves/spawn.hpp>
#include <sanguis/server/entities/enemies/create.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/angle.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/vector.hpp>
#include <sanguis/random.hpp>
#include <fcppt/math/twopi.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>
#include <cmath>
#include <fcppt/config/external_end.hpp>

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

	typedef boost::uniform_real<
		space_unit
	> uniform_su;

	typedef boost::random::variate_generator<
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
		*
		server::vector(
			std::cos(
				rand_angle
			),
			std::sin(
				rand_angle
			)
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
