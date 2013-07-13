#include <sanguis/aoe_projectile_type.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/load/aoe_projectile_name.hpp>
#include <sanguis/messages/add_aoe_projectile.hpp>
#include <sanguis/messages/create.hpp>
#include <sanguis/messages/unique_ptr.hpp>
#include <sanguis/messages/types/enum.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/direction.hpp>
#include <sanguis/server/model_name.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/projectiles/aoe_projectile.hpp>
#include <sanguis/server/entities/projectiles/life_time.hpp>
#include <sanguis/server/entities/projectiles/projectile.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>


sanguis::server::entities::projectiles::aoe_projectile::aoe_projectile(
	sanguis::diff_clock const &_diff_clock,
	sanguis::aoe_projectile_type const _type,
	sanguis::server::team const _team,
	sanguis::server::entities::movement_speed const _movement_speed,
	sanguis::server::environment::load_context &_load_context,
	sanguis::server::entities::projectiles::life_time const _life_time,
	sanguis::server::radius const _aoe,
	sanguis::server::direction const _direction
)
:
	sanguis::server::entities::projectiles::projectile(
		_diff_clock,
		sanguis::projectile_type::aoe,
		_team,
		_movement_speed,
		sanguis::server::model_name(
			sanguis::load::aoe_projectile_name(
				_type
			)
		),
		_load_context,
		_life_time,
		_direction
	),
	type_(
		_type
	),
	aoe_(
		_aoe
	)
{
}

sanguis::server::entities::projectiles::aoe_projectile::~aoe_projectile()
{
}

sanguis::server::radius const
sanguis::server::entities::projectiles::aoe_projectile::aoe() const
{
	return aoe_;
}

sanguis::messages::unique_ptr
sanguis::server::entities::projectiles::aoe_projectile::add_message(
	sanguis::server::player_id const
) const
{
	return
		sanguis::messages::create(
			sanguis::messages::add_aoe_projectile(
				this->id(),
				this->center().get(),
				this->angle().get(),
				this->speed().get(),
				aoe_.get(),
				static_cast<
					sanguis::messages::types::enum_
				>(
					type_
				)
			)
		);
}
