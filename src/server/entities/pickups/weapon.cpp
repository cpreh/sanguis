#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/pickup_type.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/load/weapon_pickup_name.hpp>
#include <sanguis/messages/add_weapon_pickup.hpp>
#include <sanguis/messages/create.hpp>
#include <sanguis/messages/unique_ptr.hpp>
#include <sanguis/server/model_name.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/with_weapon.hpp>
#include <sanguis/server/entities/pickups/optional_dim.hpp>
#include <sanguis/server/entities/pickups/pickup.hpp>
#include <sanguis/server/entities/pickups/weapon.hpp>
#include <sanguis/server/environment/load_context.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <fcppt/config/external_begin.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::pickups::weapon::weapon(
	sanguis::diff_clock const &_diff_clock,
	sanguis::server::environment::load_context &_load_context,
	sanguis::server::team const _team,
	sanguis::server::weapons::unique_ptr &&_weapon
)
:
	sanguis::server::entities::pickups::pickup(
		_diff_clock,
		sanguis::pickup_type::weapon,
		_load_context,
		_team,
		sanguis::server::entities::pickups::optional_dim(
			_load_context.entity_dim(
				sanguis::server::model_name(
					sanguis::load::weapon_pickup_name(
						_weapon->type()
					)
				)
			)
		)
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

sanguis::messages::unique_ptr
sanguis::server::entities::pickups::weapon::add_message(
	sanguis::server::player_id const
) const
{
	return
		sanguis::messages::create(
			sanguis::messages::add_weapon_pickup(
				this->id(),
				this->center().get(),
				this->angle().get(),
				weapon_->type()
			)
		);
}

void
sanguis::server::entities::pickups::weapon::do_pickup(
	sanguis::server::entities::base &_receiver
)
{
	dynamic_cast<
		sanguis::server::entities::with_weapon &
	>(
		_receiver
	)
	.pickup_weapon(
		std::move(
			weapon_
		)
	);
}
