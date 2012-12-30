#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/pickup_type.hpp>
#include <sanguis/random_generator_fwd.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/load/weapon_pickup_name.hpp>
#include <sanguis/messages/add_weapon_pickup.hpp>
#include <sanguis/messages/auto_ptr.hpp>
#include <sanguis/messages/create.hpp>
#include <sanguis/messages/types/enum.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/with_weapon.hpp>
#include <sanguis/server/entities/pickups/optional_dim.hpp>
#include <sanguis/server/entities/pickups/pickup.hpp>
#include <sanguis/server/entities/pickups/weapon.hpp>
#include <sanguis/server/environment/load_context.hpp>
#include <sanguis/server/weapons/create.hpp>
#include <sanguis/server/weapons/weapon.hpp>


sanguis::server::entities::pickups::weapon::weapon(
	sanguis::diff_clock const &_diff_clock,
	sanguis::random_generator &_random_generator,
	sanguis::server::environment::load_context &_load_context,
	sanguis::server::team const _team,
	sanguis::weapon_type const _weapon_type
)
:
	sanguis::server::entities::pickups::pickup(
		_diff_clock,
		sanguis::pickup_type::weapon,
		_load_context,
		_team,
		sanguis::server::entities::pickups::optional_dim(
			_load_context.entity_dim(
				sanguis::load::weapon_pickup_name(
					_weapon_type
				)
			)
		)
	),
	diff_clock_(
		_diff_clock
	),
	random_generator_(
		_random_generator
	),
	weapon_type_(
		_weapon_type
	)
{
}

sanguis::server::entities::pickups::weapon::~weapon()
{
}

sanguis::weapon_type
sanguis::server::entities::pickups::weapon::wtype() const
{
	return weapon_type_;
}

sanguis::messages::auto_ptr
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
				static_cast<
					sanguis::messages::types::enum_
				>(
					this->wtype()
				)
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
	.add_weapon(
		sanguis::server::weapons::create(
			diff_clock_,
			random_generator_,
			weapon_type_
		)
	);
}
