#include <sanguis/server/entities/projectiles/melee.hpp>
#include <sanguis/server/damage/list.hpp>
#include <sanguis/server/damage/wrapper.hpp>
#include <sanguis/server/damage/meta.hpp>
#include <sanguis/server/damage/normal.hpp>
#include <sanguis/server/damage/full.hpp>
#include <sanguis/duration_second.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/container/map_impl.hpp>

sanguis::server::entities::projectiles::melee::melee(
	sanguis::diff_clock const &_diff_clock,
	team::type const _team,
	damage::unit const _damage
)
:
	projectile(
		_diff_clock,
		projectile_type::melee,
		_team,
		entities::movement_speed(
			0
		),
		server::dim(
			1,
			1
		),
		projectiles::life_time(
			sanguis::duration_second(
				1.f
			)
		), // short lifetime
		server::direction(
			0
		),
		indeterminate::yes
	),
	damage_(_damage)
{
}

sanguis::server::entities::projectiles::melee::~melee()
{
}

void
sanguis::server::entities::projectiles::melee::do_damage(
	with_health &_entity
)
{
	_entity.damage(
		damage_,
		damage::list(
			damage::normal = damage::full
		)
	);

	this->expire();
}
