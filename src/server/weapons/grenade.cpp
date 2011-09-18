#include <sanguis/server/weapons/grenade.hpp>
#include <sanguis/server/weapons/delayed_attack.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/entities/projectiles/grenade.hpp>
#include <sanguis/server/environment/object.hpp>
#include <fcppt/cref.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/ref.hpp>

sanguis::server::weapons::grenade::grenade(
	sanguis::diff_clock const &_diff_clock,
	weapon_type::type const _type,
	weapons::base_cooldown const _base_cooldown,
	weapons::damage const _damage,
	weapons::aoe const _aoe,
	weapons::cast_point const _cast_point,
	weapons::reload_time const _reload_time
)
:
	weapon(
		_diff_clock,
		_type,
		weapons::range(20.f), // FIXME
		weapons::magazine_size(1),
		weapons::magazine_count(1),
		_base_cooldown,
		_cast_point,
		_reload_time
	),
	damage_(_damage),
	aoe_(_aoe)
{
}

sanguis::server::weapons::grenade::~grenade()
{
}

void
sanguis::server::weapons::grenade::do_attack(
	delayed_attack const &_attack
)
{
	_attack.environment().insert(
		entities::unique_ptr(
			fcppt::make_unique_ptr<
				entities::projectiles::grenade
			>(
				fcppt::cref(
					this->diff_clock()
				),
				fcppt::ref(
					_attack.environment().load_context()
				),
				_attack.team(),
				server::damage::unit(
					damage_
				),
				server::radius(
					aoe_.get()
				),
				_attack.dest(),
				server::direction(
					_attack.angle().get()
				)
			)
		),
		entities::insert_parameters(
			_attack.spawn_point(),
			_attack.angle()
		)
	);
}
