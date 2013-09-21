#include <sanguis/aoe_projectile_type.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/duration_second.hpp>
#include <sanguis/server/dim.hpp>
#include <sanguis/server/direction.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/vector.hpp>
#include <sanguis/server/collision/distance_pos_pos.hpp>
#include <sanguis/server/damage/fire.hpp>
#include <sanguis/server/damage/list.hpp>
#include <sanguis/server/damage/meta.hpp>
#include <sanguis/server/damage/piercing.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/damage/wrapper.hpp>
#include <sanguis/server/entities/insert_parameters_center.hpp>
#include <sanguis/server/entities/optional_base_ref.hpp>
#include <sanguis/server/entities/transfer_parameters.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/with_health_fwd.hpp>
#include <sanguis/server/entities/projectiles/aoe_damage.hpp>
#include <sanguis/server/entities/projectiles/aoe_projectile.hpp>
#include <sanguis/server/entities/projectiles/damage_per_pulse.hpp>
#include <sanguis/server/entities/projectiles/grenade.hpp>
#include <sanguis/server/entities/projectiles/life_time.hpp>
#include <sanguis/server/entities/projectiles/pulse_time.hpp>
#include <sanguis/server/entities/projectiles/pulses.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sge/timer/reset_when_expired.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <algorithm>
#include <chrono>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::projectiles::grenade::grenade(
	sanguis::diff_clock const &_diff_clock,
	sanguis::server::environment::load_context &_load_context,
	sanguis::server::team const _team,
	sanguis::server::damage::unit const _damage,
	sanguis::server::radius const _aoe,
	sanguis::server::vector const &_dest,
	sanguis::server::direction const _direction
)
:
	sanguis::server::entities::projectiles::aoe_projectile(
		_diff_clock,
		sanguis::aoe_projectile_type::grenade,
		_team,
		sanguis::server::entities::movement_speed(
			500.f
		),
		_load_context,
		sanguis::server::entities::projectiles::life_time(
			sanguis::duration_second(
				2.f
			)
		),
		_aoe,
		_direction
	),
	diff_clock_(
		_diff_clock
	),
	slowdown_timer_(
		sanguis::diff_timer::parameters(
			_diff_clock,
			std::chrono::milliseconds(
				100
			)
		)
	),
	damage_(
		_damage
	),
	dest_(
		_dest
	)
{
}

sanguis::server::entities::projectiles::grenade::~grenade()
{
}

bool
sanguis::server::entities::projectiles::grenade::on_transfer(
	sanguis::server::entities::transfer_parameters const &_param
)
{
	if(
		!sanguis::server::entities::with_body::on_transfer(
			_param
		)
	)
		return false;

	this->movement_speed().current(
		std::min(
			this->movement_speed().max(),
			sanguis::server::collision::distance_pos_pos(
				_param.center().get(),
				dest_
			)
		)
	);

	return true;
}

void
sanguis::server::entities::projectiles::grenade::do_damage(
	sanguis::server::entities::with_health &
)
{
}

void
sanguis::server::entities::projectiles::grenade::on_update()
{
	if(
		sge::timer::reset_when_expired(
			slowdown_timer_
		)
	)
		this->movement_speed().current(
			this->movement_speed().current()
			* 0.9f
		);
}

void
sanguis::server::entities::projectiles::grenade::on_remove()
{
	this->environment().insert(
		fcppt::make_unique_ptr<
			sanguis::server::entities::projectiles::aoe_damage
		>(
			diff_clock_,
			this->team(),
			this->aoe(),
			sanguis::server::entities::projectiles::damage_per_pulse(
				damage_
			),
			sanguis::server::entities::projectiles::pulses(
				1u
			),
			sanguis::server::entities::projectiles::pulse_time(
				sanguis::duration_second(
					0.1f
				)
			),
			sanguis::server::damage::list(
				sanguis::server::damage::piercing =
					sanguis::server::damage::unit(
						0.5f
					)
			)(
				sanguis::server::damage::fire =
					sanguis::server::damage::unit(
						0.5f
					)
			)
		),
		sanguis::server::entities::insert_parameters_center(
			this->center()
		)
	);
}
