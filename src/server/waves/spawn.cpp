#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/enemy_type.hpp>
#include <sanguis/random_generator.hpp>
#include <sanguis/server/angle.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/vector.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/entities/enemies/create.hpp>
#include <sanguis/server/entities/enemies/spawn_owner_fwd.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/waves/spawn.hpp>
#include <fcppt/math/twopi.hpp>
#include <fcppt/math/vector/arithmetic.hpp>
#include <fcppt/random/variate.hpp>
#include <fcppt/random/distribution/uniform_real.hpp>
#include <fcppt/config/external_begin.hpp>
#include <cmath>
#include <fcppt/config/external_end.hpp>


void
sanguis::server::waves::spawn(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
	sanguis::server::environment::object &_env,
	sanguis::server::environment::load_context &_load_context,
	sanguis::enemy_type const _etype,
	sanguis::server::entities::enemies::spawn_owner const &_spawn
)
{
	typedef fcppt::random::distribution::uniform_real<
		sanguis::server::space_unit
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

	sanguis::server::space_unit const
		rand_angle(
			rng()
		),
		radius(
			static_cast<
				sanguis::server::space_unit
			>(
				10
			)
		),
		scale(
			static_cast<
				sanguis::server::space_unit
			>(
				1.5
			)
		);

	sanguis::server::angle const angle(
		static_cast<
			sanguis::server::space_unit
		>(
			0
		)
	);

	sanguis::server::center const center(
		scale
		* radius
		*
		sanguis::server::vector(
			std::cos(
				rand_angle
			),
			std::sin(
				rand_angle
			)
		)
	);

	_env.insert(
		sanguis::server::entities::enemies::create(
			_diff_clock,
			_random_generator,
			_etype,
			_load_context,
			_spawn
		),
		sanguis::server::entities::insert_parameters(
			center,
			angle
		)
	);
}
