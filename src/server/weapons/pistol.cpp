#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/string_vector.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/insert_parameters.hpp>
#include <sanguis/server/entities/projectiles/simple_bullet.hpp>
#include <sanguis/server/environment/insert_no_result.hpp>
#include <sanguis/server/environment/object.hpp>
#include <sanguis/server/weapons/attack_result.hpp>
#include <sanguis/server/weapons/base_cooldown.hpp>
#include <sanguis/server/weapons/delayed_attack.hpp>
#include <sanguis/server/weapons/make_attribute.hpp>
#include <sanguis/server/weapons/optional_magazine_size.hpp>
#include <sanguis/server/weapons/optional_reload_time.hpp>
#include <sanguis/server/weapons/pistol.hpp>
#include <sanguis/server/weapons/pistol_parameters.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <fcppt/insert_to_fcppt_string.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/text.hpp>


sanguis::server::weapons::pistol::pistol(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
	sanguis::weapon_type const _weapon_type,
	sanguis::server::weapons::pistol_parameters const &_parameters
)
:
	sanguis::server::weapons::weapon(
		_diff_clock,
		_random_generator,
		_weapon_type,
		_parameters.accuracy(),
		_parameters.range(),
		sanguis::server::weapons::optional_magazine_size(
			_parameters.magazine_size()
		),
		_parameters.base_cooldown(),
		_parameters.cast_point(),
		sanguis::server::weapons::optional_reload_time(
			_parameters.reload_time()
		)
	),
	damage_(
		_parameters.damage()
	)
{
}

sanguis::server::weapons::pistol::~pistol()
{
}

sanguis::server::weapons::attack_result
sanguis::server::weapons::pistol::do_attack(
	sanguis::server::weapons::delayed_attack const &_attack
)
{
	sanguis::server::environment::insert_no_result(
		_attack.environment(),
		fcppt::make_unique_ptr<
			sanguis::server::entities::projectiles::simple_bullet
		>(
			this->diff_clock(),
			_attack.environment().load_context(),
			_attack.team(),
			damage_,
			sanguis::server::direction(
				_attack.angle().get()
			)
		),
		sanguis::server::entities::insert_parameters(
			_attack.spawn_point(),
			_attack.angle()
		)
	);

	return
		sanguis::server::weapons::attack_result::success;
}

sanguis::string_vector
sanguis::server::weapons::pistol::attributes() const
{
	return
		sanguis::string_vector{
			sanguis::server::weapons::make_attribute(
				FCPPT_TEXT("damage"),
				fcppt::insert_to_fcppt_string(
					damage_
				)
			)
		};
}
