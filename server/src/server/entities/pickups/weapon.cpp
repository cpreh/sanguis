#include <sanguis/weapon_description.hpp>
#include <sanguis/weapon_type.hpp>
#include <sanguis/collision/world/group.hpp>
#include <sanguis/load/weapon_pickup_name.hpp>
#include <sanguis/messages/convert/to_magazine_size.hpp>
#include <sanguis/messages/convert/to_weapon_attribute_vector.hpp>
#include <sanguis/messages/roles/angle.hpp>
#include <sanguis/messages/roles/center.hpp>
#include <sanguis/messages/roles/entity_id.hpp>
#include <sanguis/messages/roles/magazine_base_size.hpp>
#include <sanguis/messages/roles/magazine_extra_size.hpp>
#include <sanguis/messages/roles/magazine_remaining.hpp>
#include <sanguis/messages/roles/weapon_attribute_container.hpp>
#include <sanguis/messages/roles/weapon_type.hpp>
#include <sanguis/messages/server/add_weapon_pickup.hpp>
#include <sanguis/messages/server/create_ptr.hpp>
#include <sanguis/messages/server/unique_ptr.hpp>
#include <sanguis/server/model_name.hpp>
#include <sanguis/server/model_size.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/entities/with_links.hpp>
#include <sanguis/server/entities/pickups/weapon.hpp>
#include <sanguis/server/environment/load_context.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <fcppt/assert/pre.hpp>
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
		_load_context.model_size(
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
	// TODO: Should we make a function for this?
	sanguis::server::weapons::unique_ptr result(
		std::move(
			*weapon_
		)
	);

	weapon_.reset();

	return
		std::move(
			result
		);
}

sanguis::weapon_type const
sanguis::server::entities::pickups::weapon::weapon_type() const
{
	return
		this->get().type();
}

bool
sanguis::server::entities::pickups::weapon::dead() const
{
	return
		!weapon_;
}

sanguis::server::team
sanguis::server::entities::pickups::weapon::team() const
{
	return
		team_;
}

sanguis::collision::world::group
sanguis::server::entities::pickups::weapon::collision_group() const
{
	return
		sanguis::collision::world::group::weapon_pickup;
}

sanguis::messages::server::unique_ptr
sanguis::server::entities::pickups::weapon::add_message(
	sanguis::server::player_id const
) const
{
	sanguis::weapon_description const description(
		this->get().description()
	);

	return
		sanguis::messages::server::create_ptr(
			sanguis::messages::server::add_weapon_pickup(
				sanguis::messages::roles::entity_id{} =
					this->id(),
				sanguis::messages::roles::center{} =
					this->center().get(),
				sanguis::messages::roles::angle{} =
					this->angle().get(),
				sanguis::messages::roles::weapon_type{} =
					description.weapon_type(),
				// TODO: Unify this with give_weapon
				sanguis::messages::roles::magazine_base_size{} =
					sanguis::messages::convert::to_magazine_size(
						description.magazine_size().get()
					),
				sanguis::messages::roles::magazine_extra_size{} =
					sanguis::messages::convert::to_magazine_size(
						description.magazine_extra().get()
					),
				sanguis::messages::roles::magazine_remaining{} =
					sanguis::messages::convert::to_magazine_size(
						description.magazine_remaining().get()
					),
				sanguis::messages::roles::weapon_attribute_container{} =
					sanguis::messages::convert::to_weapon_attribute_vector(
						description.attributes()
					)

			)
		);
}

sanguis::server::weapons::weapon &
sanguis::server::entities::pickups::weapon::get() const
{
	FCPPT_ASSERT_PRE(
		weapon_
	);

	return
		**weapon_;
}
