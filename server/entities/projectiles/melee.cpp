#include "melee.hpp"
#include "../../damage/list.hpp"
#include "../../damage/wrapper.hpp"
#include "../../damage/meta.hpp"
#include "../../damage/normal.hpp"
#include "../../damage/full.hpp"
#include <fcppt/math/dim/basic_impl.hpp>
#include <fcppt/container/map_impl.hpp>
#include <boost/assign/list_of.hpp>

sanguis::server::entities::projectiles::melee::melee(
	team::type const _team,
	damage::unit const _damage
)
:
	projectile(
		projectile_type::melee,
		_team,
		entities::movement_speed(
			0
		),
		dim_type(
			1,
			1
		),
		life_time(
			1
		), // short lifetime
		static_cast<space_unit>(0),
		indeterminate::yes
	),
	damage_(_damage)
{}

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

	expire();
}
