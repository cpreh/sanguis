#include <sanguis/aoe_projectile_type.hpp>
#include <sanguis/load/aoe_projectile_name.hpp>
#include <sanguis/messages/roles/angle.hpp>
#include <sanguis/messages/roles/aoe.hpp>
#include <sanguis/messages/roles/aoe_projectile_type.hpp>
#include <sanguis/messages/roles/center.hpp>
#include <sanguis/messages/roles/entity_id.hpp>
#include <sanguis/messages/roles/speed.hpp>
#include <sanguis/messages/server/add_aoe_projectile.hpp>
#include <sanguis/messages/server/create_ptr.hpp>
#include <sanguis/messages/server/unique_ptr.hpp>
#include <sanguis/server/aoe.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/direction.hpp>
#include <sanguis/server/model_name.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/projectiles/aoe_projectile.hpp>
#include <sanguis/server/entities/projectiles/life_time.hpp>
#include <sanguis/server/entities/projectiles/projectile.hpp>
#include <sanguis/server/environment/load_context_fwd.hpp>


sanguis::server::entities::projectiles::aoe_projectile::aoe_projectile(
	sanguis::aoe_projectile_type const _type,
	sanguis::server::team const _team,
	sanguis::server::entities::movement_speed const _movement_speed,
	sanguis::server::environment::load_context &_load_context,
	sanguis::server::entities::projectiles::life_time const _life_time,
	sanguis::server::aoe const _aoe,
	sanguis::server::direction const _direction
)
:
	sanguis::server::entities::projectiles::projectile(
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

sanguis::server::aoe const
sanguis::server::entities::projectiles::aoe_projectile::aoe() const
{
	return aoe_;
}

sanguis::messages::server::unique_ptr
sanguis::server::entities::projectiles::aoe_projectile::add_message(
	sanguis::server::player_id const
) const
{
	return
		sanguis::messages::server::create_ptr(
			sanguis::messages::server::add_aoe_projectile(
				sanguis::messages::roles::entity_id{} =
					this->id(),
				sanguis::messages::roles::center{} =
					this->center().get(),
				sanguis::messages::roles::angle{} =
					this->angle().get(),
				sanguis::messages::roles::speed{} =
					this->speed().get(),
				sanguis::messages::roles::aoe{} =
					aoe_.get(),
				sanguis::messages::roles::aoe_projectile_type{} =
					type_
			)
		);
}
