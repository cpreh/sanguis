#include <sanguis/weapon_type.hpp>
#include <sanguis/collision/world/group.hpp>
#include <sanguis/collision/world/group_field.hpp>
#include <sanguis/load/weapon_pickup_name.hpp>
#include <sanguis/messages/server/add_weapon_pickup.hpp>
#include <sanguis/messages/server/create_ptr.hpp>
#include <sanguis/messages/server/unique_ptr.hpp>
#include <sanguis/server/dim.hpp>
#include <sanguis/server/model_name.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/entities/with_links.hpp>
#include <sanguis/server/entities/pickups/weapon.hpp>
#include <sanguis/server/environment/load_context.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::pickups::weapon::weapon(
	sanguis::server::environment::load_context &_load_context,
	sanguis::server::team const _team,
	sanguis::server::weapons::unique_ptr &&_weapon
)
:
	sanguis::server::entities::ifaces::with_team(),
	sanguis::server::entities::with_body(
		_load_context.entity_dim(
			sanguis::server::model_name(
				sanguis::load::weapon_pickup_name(
					_weapon->type()
				)
			)
		)
	),
	sanguis::server::entities::with_id(
		_load_context.next_id()
	),
	sanguis::server::entities::with_links(),
	team_(
		_team
	),
	weapon_(
		std::move(
			_weapon
		)
	)
{
}

sanguis::server::entities::pickups::weapon::~weapon()
{
}

sanguis::server::weapons::unique_ptr
sanguis::server::entities::pickups::weapon::obtain()
{
	return
		std::move(
			weapon_
		);
}

sanguis::weapon_type const
sanguis::server::entities::pickups::weapon::weapon_type() const
{
	return
		weapon_->type();
}

bool
sanguis::server::entities::pickups::weapon::dead() const
{
	return
		!weapon_
		||
		!weapon_->usable();
}

sanguis::server::team
sanguis::server::entities::pickups::weapon::team() const
{
	return
		team_;
}

sanguis::collision::world::group_field const
sanguis::server::entities::pickups::weapon::collision_groups() const
{
	return
		sanguis::collision::world::group_field{
			sanguis::collision::world::group::weapon_pickup
		};
}

sanguis::messages::server::unique_ptr
sanguis::server::entities::pickups::weapon::add_message(
	sanguis::server::player_id const
) const
{
	return
		sanguis::messages::server::create_ptr(
			sanguis::messages::server::add_weapon_pickup(
				this->id(),
				this->center().get(),
				this->angle().get(),
				weapon_->type()
			)
		);
}
