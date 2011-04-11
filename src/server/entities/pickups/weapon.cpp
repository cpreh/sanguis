#include "weapon.hpp"
#include "../with_weapon.hpp"
#include "../../weapons/weapon.hpp"
#include "../../weapons/create.hpp"
#include "../../environment/load_context.hpp"
#include "../../../load/weapon_pickup_name.hpp"
#include "../../../messages/create.hpp"
#include "../../../messages/add_weapon_pickup.hpp"
#include <fcppt/optional_impl.hpp>
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>

sanguis::server::entities::pickups::weapon::weapon(
	server::environment::load_context &_load_context,
	server::team::type const _team,
	weapon_type::type const _weapon_type
)
:
	pickup(
		pickup_type::weapon,
		_load_context,
		_team,
		_load_context.entity_dim(
			load::weapon_pickup_name(
				_weapon_type
			)
		)
	),
	weapon_type_(_weapon_type)
{
}

sanguis::server::entities::pickups::weapon::~weapon()
{
}

sanguis::weapon_type::type
sanguis::server::entities::pickups::weapon::wtype() const
{
	return weapon_type_;
}

sanguis::messages::auto_ptr
sanguis::server::entities::pickups::weapon::add_message(
	player_id const
) const
{
	return
		messages::create(
			messages::add_weapon_pickup(
				this->id(),
				this->center().get(),
				this->angle().get(),
				this->wtype()
			)
		);
}

void
sanguis::server::entities::pickups::weapon::do_pickup(
	base &_receiver
)
{
	dynamic_cast<
		with_weapon &
	>(
		_receiver
	)
	.add_weapon(
		weapons::create(
			weapon_type_
		)
	);
}
