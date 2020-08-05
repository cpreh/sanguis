#include <sanguis/perk_type.hpp>
#include <sanguis/random_generator.hpp>
#include <sanguis/random_variate_impl.hpp>
#include <sanguis/server/aoe.hpp>
#include <sanguis/server/direction.hpp>
#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/damage/explosive.hpp>
#include <sanguis/server/damage/full.hpp>
#include <sanguis/server/damage/make_array.hpp>
#include <sanguis/server/damage/piercing.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/entities/modify_damages.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/entities/with_perks.hpp>
#include <sanguis/server/entities/projectiles/rocket.hpp>
#include <sanguis/server/entities/projectiles/simple_bullet.hpp>
#include <sanguis/server/environment/insert_no_result.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/perks/choleric.hpp>
#include <sanguis/server/perks/level_diff.hpp>
#include <sanguis/server/perks/perk.hpp>
#include <sge/timer/reset_when_expired.hpp>
#include <fcppt/literal.hpp>
#include <fcppt/make_cref.hpp>
#include <fcppt/make_ref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/unique_ptr_to_base.hpp>
#include <fcppt/algorithm/repeat.hpp>
#include <fcppt/math/twopi.hpp>
#include <fcppt/random/distribution/basic_impl.hpp>
#include <fcppt/random/distribution/parameters/uniform_real_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <chrono>
#include <fcppt/config/external_end.hpp>


sanguis::server::perks::choleric::choleric(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator
)
:
	sanguis::server::perks::perk(
		sanguis::perk_type::choleric
	),
	shoot_timer_(
		sanguis::diff_timer::parameters(
			fcppt::make_cref(
				_diff_clock
			),
			std::chrono::seconds(
				5
			)
		)
	),
	rand_(
		fcppt::make_ref(
			_random_generator
		),
		sanguis::server::perks::choleric::distribution(
			sanguis::server::perks::choleric::distribution::param_type::min(
				0.f
			),
			sanguis::server::perks::choleric::distribution::param_type::sup(
				fcppt::math::twopi<
					sanguis::server::space_unit
				>()
			)
		)
	)
{
}

sanguis::server::perks::choleric::~choleric()
{
}

void
sanguis::server::perks::choleric::update(
	sanguis::server::entities::with_perks &_entity,
	sanguis::server::environment::object &_env
)
{
	if(
		!sge::timer::reset_when_expired(
			fcppt::make_ref(
				shoot_timer_
			)
		)
	)
		return;

	sanguis::server::level const rocket_level(
		10u
	);

	bool const spawn_bullets(
		this->level() < rocket_level
	);

	fcppt::algorithm::repeat(
		spawn_bullets
		?
			fcppt::literal<
				sanguis::server::level::value_type
			>(
				3
			)
			+
			this->level().get()
			*
			fcppt::literal<
				sanguis::server::level::value_type
			>(
				2
			)
		:
			this->level().get()
		,
		[
			this,
			&_env,
			&_entity,
			spawn_bullets
		]
		()
		{
			sanguis::server::direction const direction(
				rand_()
			);

			sanguis::server::environment::insert_no_result(
				_env,
				spawn_bullets
				?
					fcppt::unique_ptr_to_base<
						sanguis::server::entities::with_id
					>(
						fcppt::make_unique_ptr<
							sanguis::server::entities::projectiles::simple_bullet
						>(
							_env.load_context(),
							_entity.team(),
							sanguis::server::damage::unit(
								10.f
							),
							sanguis::server::entities::modify_damages(
								_entity,
								sanguis::server::damage::make_array({
									sanguis::server::damage::piercing =
										sanguis::server::damage::full
								})
							),
							direction
						)
					)
				:
					fcppt::unique_ptr_to_base<
						sanguis::server::entities::with_id
					>(
						fcppt::make_unique_ptr<
							sanguis::server::entities::projectiles::rocket
						>(
							_env.load_context(),
							_entity.team(),
							sanguis::server::damage::unit(
								15.f
							),
							sanguis::server::entities::modify_damages(
								_entity,
								sanguis::server::damage::explosive()
							),
							sanguis::server::aoe(
								90.f
							),
							direction
						)
					)
				,
				sanguis::server::entities::insert_parameters(
					_entity.center(),
					sanguis::server::angle(
						direction.get()
					)
				)
			);
		}
	);
}

void
sanguis::server::perks::choleric::change(
	sanguis::server::entities::with_perks &,
	sanguis::server::perks::level_diff
)
{
}
