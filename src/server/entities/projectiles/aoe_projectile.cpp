#include <sanguis/aoe_projectile_type.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/messages/add_aoe_projectile.hpp>
#include <sanguis/messages/auto_ptr.hpp>
#include <sanguis/messages/create.hpp>
#include <sanguis/messages/types/enum.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/dim_fwd.hpp>
#include <sanguis/server/direction.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/projectiles/aoe_projectile.hpp>
#include <sanguis/server/entities/projectiles/life_time.hpp>
#include <sanguis/server/entities/projectiles/indeterminate.hpp>
#include <sanguis/server/entities/projectiles/projectile.hpp>


sanguis::server::entities::projectiles::aoe_projectile::aoe_projectile(
	sanguis::diff_clock const &_diff_clock,
	sanguis::aoe_projectile_type const _type,
	sanguis::server::team const _team,
	sanguis::server::entities::movement_speed const _movement_speed,
	sanguis::server::dim const &_dim,
	sanguis::server::entities::projectiles::life_time const _life_time,
	sanguis::server::entities::projectiles::indeterminate const _indeterminate,
	sanguis::server::radius const _aoe,
	sanguis::server::direction const _direction
)
:
	sanguis::server::entities::projectiles::projectile(
		_diff_clock,
		sanguis::projectile_type::aoe,
		_team,
		_movement_speed,
		_dim,
		_life_time,
		_direction,
		_indeterminate
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

sanguis::messages::auto_ptr
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
