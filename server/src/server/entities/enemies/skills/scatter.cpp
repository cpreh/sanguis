#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/server/angle.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/direction.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/damage/explosive.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/entities/modify_damages.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/entities/enemies/attribute.hpp>
#include <sanguis/server/entities/enemies/enemy.hpp>
#include <sanguis/server/entities/enemies/skills/cooldown.hpp>
#include <sanguis/server/entities/enemies/skills/scatter.hpp>
#include <sanguis/server/entities/enemies/skills/skill.hpp>
#include <sanguis/server/entities/projectiles/rocket.hpp>
#include <sanguis/server/entities/projectiles/scatter.hpp>
#include <sanguis/server/entities/projectiles/scatter_create.hpp>
#include <sanguis/server/environment/insert_no_result.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sge/timer/reset_when_expired.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/maybe_void.hpp>
#include <fcppt/text.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/algorithm/repeat.hpp>


sanguis::server::entities::enemies::skills::scatter::scatter(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
	sanguis::server::entities::enemies::skills::cooldown const _cooldown
)
:
	sanguis::server::entities::enemies::skills::skill(),
	random_generator_(
		_random_generator
	),
	cooldown_timer_(
		sanguis::diff_timer::parameters(
			_diff_clock,
			_cooldown.get()
		)
	)
{
}

sanguis::server::entities::enemies::skills::scatter::~scatter()
{
}

void
sanguis::server::entities::enemies::skills::scatter::update(
	sanguis::server::entities::enemies::enemy &_entity
)
{
	if(
		!sge::timer::reset_when_expired(
			cooldown_timer_
		)
	)
		return;

	fcppt::maybe_void(
		_entity.environment(),
		[
			this,
			&_entity
		](
			sanguis::server::environment::object &_environment
		)
		{
			fcppt::algorithm::repeat(
				// TODO
				5,
				[
					this,
					&_entity,
					&_environment
				]
				{
					sanguis::server::damage::modified_array const damage_modifiers(
						sanguis::server::entities::modify_damages(
							_entity,
							sanguis::server::damage::explosive()
						)
					);

					sanguis::server::environment::insert_no_result(
						_environment,
						fcppt::unique_ptr_to_base<
							sanguis::server::entities::with_id
						>(
							fcppt::make_unique_ptr<
								sanguis::server::entities::projectiles::scatter
							>(
								random_generator_,
								_environment.load_context(),
								_entity.team(),
								sanguis::server::direction(
									_entity.angle().get()
								),
								sanguis::server::entities::projectiles::scatter_create(
									[
										damage_modifiers
									](
										sanguis::server::environment::object &_env,
										sanguis::server::team const _team,
										sanguis::server::angle const _angle
									)
									{
										return
											fcppt::unique_ptr_to_base<
												sanguis::server::entities::with_id
											>(
												fcppt::make_unique_ptr<
													sanguis::server::entities::projectiles::rocket
												>(
													_env.load_context(),
													_team,
													// TODO
													sanguis::server::damage::unit(
														10.f
													),
													damage_modifiers,
													// TODO
													sanguis::server::aoe(
														100.f
													),
													sanguis::server::direction(
														_angle.get()
													)
												)
											);
									}
								)
							)
						),
						sanguis::server::entities::insert_parameters(
							_entity.center(),
							_entity.angle()
						)
					);
				}
			);
		}
	);
}

sanguis::server::entities::enemies::attribute
sanguis::server::entities::enemies::skills::scatter::attribute() const
{
	return
		sanguis::server::entities::enemies::attribute(
			FCPPT_TEXT("scattering")
		);
}
