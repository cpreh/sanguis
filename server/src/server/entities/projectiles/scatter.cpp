#include <sanguis/diff_timer.hpp>
#include <sanguis/duration_second.hpp>
#include <sanguis/projectile_type.hpp>
#include <sanguis/random_variate_impl.hpp>
#include <sanguis/server/angle.hpp>
#include <sanguis/server/direction.hpp>
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
#include <fcppt/reference_impl.hpp>
#include <fcppt/math/twopi.hpp>
#include <fcppt/optional/maybe_void.hpp>
#include <fcppt/preprocessor/disable_vc_warning.hpp>
#include <fcppt/preprocessor/pop_warning.hpp>
#include <fcppt/preprocessor/push_warning.hpp>
#include <fcppt/random/distribution/basic_impl.hpp>
#include <fcppt/random/distribution/parameters/uniform_real_impl.hpp>


FCPPT_PP_PUSH_WARNING
FCPPT_PP_DISABLE_VC_WARNING(4355)

sanguis::server::entities::projectiles::scatter::scatter(
	sanguis::random_generator &_random_generator,
	sanguis::server::environment::load_context &_load_context,
	sanguis::server::team const _team,
	sanguis::server::direction const _direction,
	sanguis::server::entities::projectiles::scatter_create const &_create
)
:
	sanguis::server::entities::projectiles::projectile(
		sanguis::projectile_type::bullet,
		_team,
		sanguis::server::entities::movement_speed(
			300.f
		),
		// TODO
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
			this->diff_clock(),
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

FCPPT_PP_POP_WARNING

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

	fcppt::optional::maybe_void(
		this->environment(),
		[
			this
		](
			fcppt::reference<
				sanguis::server::environment::object
			> const _environment
		)
		{
			sanguis::server::angle const random_angle(
				angle_rng_()
			);

			sanguis::server::environment::insert_no_result(
				_environment.get(),
				create_(
					_environment.get(),
					this->team(),
					random_angle
				),
				sanguis::server::entities::insert_parameters(
					this->center(),
					random_angle
				)
			);
		}
	);
}

void
sanguis::server::entities::projectiles::scatter::do_damage(
	sanguis::server::entities::with_health &
)
{
}
