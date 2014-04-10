#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/duration_second.hpp>
#include <sanguis/projectile_type.hpp>
#include <sanguis/random_variate_impl.hpp>
#include <sanguis/server/angle.hpp>
#include <sanguis/server/direction.hpp>
#include <sanguis/server/model_name.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/with_health_fwd.hpp>
#include <sanguis/server/entities/projectiles/life_time.hpp>
#include <sanguis/server/entities/projectiles/projectile.hpp>
#include <sanguis/server/entities/projectiles/scatter.hpp>
#include <sanguis/server/entities/projectiles/scatter_create.hpp>
#include <sanguis/server/environment/insert_no_result.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/environment/optional_object_ref.hpp>
#include <sge/timer/reset_when_expired.hpp>
#include <fcppt/text.hpp>
#include <fcppt/math/twopi.hpp>
#include <fcppt/random/distribution/basic_impl.hpp>
#include <fcppt/random/distribution/parameters/uniform_real_impl.hpp>


sanguis::server::entities::projectiles::scatter::scatter(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
	sanguis::server::environment::load_context &_load_context,
	sanguis::server::team const _team,
	sanguis::server::direction const _direction,
	sanguis::server::entities::projectiles::scatter_create const &_create
)
:
	sanguis::server::entities::projectiles::projectile(
		_diff_clock,
		sanguis::projectile_type::simple_bullet,
		_team,
		sanguis::server::entities::movement_speed(
			300.f
		),
		// TODO
		sanguis::server::model_name(
			FCPPT_TEXT("bullet")
		),
		_load_context,
		sanguis::server::entities::projectiles::life_time(
			sanguis::duration_second(
				10.f
			)
		),
		_direction
	),
	create_(
		_create
	),
	shoot_timer_(
		sanguis::diff_timer::parameters(
			_diff_clock,
			// TODO
			sanguis::duration_second(
				0.5f
			)
		)
		.expired(
			true
		)
	),
	angle_rng_(
		_random_generator,
		angle_distribution::param_type(
			angle_distribution::param_type::min(
				sanguis::server::angle(
					0.f
				)
			),
			angle_distribution::param_type::sup(
				sanguis::server::angle(
					fcppt::math::twopi<
						sanguis::server::angle::value_type
					>()
				)
			)
		)
	)
{
}

sanguis::server::entities::projectiles::scatter::~scatter()
{
}

void
sanguis::server::entities::projectiles::scatter::update()
{
	sanguis::server::entities::projectiles::projectile::update();

	if(
		!sge::timer::reset_when_expired(
			shoot_timer_
		)
	)
		return;


	sanguis::server::angle const random_angle(
		angle_rng_()
	);

	sanguis::server::environment::optional_object_ref const env(
		this->environment()
	);

	if(
		!env
	)
		return;

	sanguis::server::environment::insert_no_result(
		*env,
		create_(
			*env,
			this->team(),
			random_angle
		),
		sanguis::server::entities::insert_parameters(
			this->center(),
			random_angle
		)
	);
}

void
sanguis::server::entities::projectiles::scatter::do_damage(
	sanguis::server::entities::with_health &
)
{
}
