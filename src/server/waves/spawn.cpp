#include <sanguis/random_generator.hpp>
#include <sanguis/server/waves/spawn.hpp>
#include <sanguis/server/entities/enemies/create.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/angle.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/vector.hpp>
#include <fcppt/math/twopi.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/math/vector/object_impl.hpp>
#include <fcppt/math/dim/object_impl.hpp>
#include <fcppt/random/variate.hpp>
#include <fcppt/random/distribution/uniform_real.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cmath>
#include <fcppt/config/external_end.hpp>

void
sanguis::server::waves::spawn(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
	environment::object &_env,
	environment::load_context &_load_context,
	enemy_type::type const _etype,
	entities::auto_weak_link const _spawn
)
{
	typedef fcppt::random::distribution::uniform_real<
		server::space_unit
	> angle_distribution;

	typedef fcppt::random::variate<
		sanguis::random_generator,
		angle_distribution
	> rng_type;

	rng_type rng(
		_random_generator,
		angle_distribution(
			angle_distribution::min(
				0.f
			),
			angle_distribution::sup(
				fcppt::math::twopi<
					server::space_unit
				>()
			)
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
			_random_generator,
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
