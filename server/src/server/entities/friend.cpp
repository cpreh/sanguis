#include <sanguis/friend_type.hpp>
#include <sanguis/collision/world/body_group.hpp>
#include <sanguis/collision/world/created.hpp>
#include <sanguis/load/model/friend_path.hpp>
#include <sanguis/messages/roles/angle.hpp>
#include <sanguis/messages/roles/aura_type_container.hpp>
#include <sanguis/messages/roles/buff_type_container.hpp>
#include <sanguis/messages/roles/center.hpp>
#include <sanguis/messages/roles/created.hpp>
#include <sanguis/messages/roles/entity_id.hpp>
#include <sanguis/messages/roles/friend_type.hpp>
#include <sanguis/messages/roles/health.hpp>
#include <sanguis/messages/roles/max_health.hpp>
#include <sanguis/messages/roles/primary_weapon.hpp>
#include <sanguis/messages/roles/speed.hpp>
#include <sanguis/messages/roles/weapon_status.hpp>
#include <sanguis/messages/server/add_friend.hpp>
#include <sanguis/messages/server/create_ptr.hpp>
#include <sanguis/messages/server/unique_ptr.hpp>
#include <sanguis/server/dim.hpp>
#include <sanguis/server/health.hpp>
#include <sanguis/server/model_size.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/regeneration.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/ai/create_function.hpp>
#include <sanguis/server/auras/aura.hpp>
#include <sanguis/server/auras/container.hpp>
#include <sanguis/server/collision/with_world.hpp>
#include <sanguis/server/damage/armor_array.hpp>
#include <sanguis/server/entities/friend.hpp>
#include <sanguis/server/entities/movement_speed.hpp>
#include <sanguis/server/entities/movement_speed_initial.hpp>
#include <sanguis/server/entities/optional_transfer_result.hpp>
#include <sanguis/server/entities/transfer_parameters.hpp>
#include <sanguis/server/entities/with_ai.hpp>
#include <sanguis/server/entities/with_auras.hpp>
#include <sanguis/server/entities/with_buffs.hpp>
#include <sanguis/server/entities/with_health.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/entities/with_links.hpp>
#include <sanguis/server/entities/with_velocity.hpp>
#include <sanguis/server/entities/ifaces/with_team.hpp>
#include <sanguis/server/entities/pickups/pickup.hpp>
#include <sanguis/server/entities/property/initial_zero.hpp>
#include <sanguis/server/environment/load_context.hpp>
#include <sanguis/server/weapons/default_ias.hpp>
#include <sanguis/server/weapons/default_irs.hpp>
#include <sanguis/server/weapons/unique_ptr.hpp>
#include <sanguis/server/weapons/weapon.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/logic/tribool.hpp>
#include <utility>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::friend_::friend_(
	sanguis::friend_type const _friend_type,
	sanguis::server::environment::load_context &_load_context,
	sanguis::server::damage::armor_array const &_armor,
	sanguis::server::health const _health,
	sanguis::server::entities::movement_speed const _movement_speed,
	sanguis::server::ai::create_function const &_ai,
	sanguis::server::weapons::unique_ptr &&_weapon
)
:
	sanguis::server::entities::ifaces::with_team(),
	sanguis::server::entities::with_ai(
		_ai,
		std::move(
			_weapon
		),
		sanguis::server::auras::container(),
		sanguis::server::weapons::default_ias(),
		sanguis::server::weapons::default_irs()
	),
	sanguis::server::entities::with_buffs(),
	sanguis::server::entities::with_id(
		_load_context.next_id()
	),
	sanguis::server::entities::with_health(
		_health,
		sanguis::server::regeneration(
			0.f
		),
		_armor
	),
	sanguis::server::entities::with_links(),
	sanguis::server::entities::with_velocity(
		_load_context.model_size(
			sanguis::load::model::friend_path(
				_friend_type
			)
		),
		sanguis::server::entities::movement_speed_initial(
			sanguis::server::entities::property::initial_zero(
				_movement_speed.get()
			)
		),
		sanguis::server::direction(
			0.f
		)
	),
	friend_type_(
		_friend_type
	)
{
}

sanguis::server::entities::optional_transfer_result
sanguis::server::entities::friend_::on_transfer(
	sanguis::server::entities::transfer_parameters const &_parameters
)
{
	if(
		sanguis::server::collision::with_world(
			_parameters.center(),
			this->dim(),
			_parameters.grid()
		)
	)
		return
			sanguis::server::entities::optional_transfer_result();

	// TODO: Why?
	sanguis::server::entities::with_auras::on_transfer(
		_parameters
	);

	return
		sanguis::server::entities::with_velocity::on_transfer(
			_parameters
		);
}

void
sanguis::server::entities::friend_::update()
{
	sanguis::server::entities::with_ai::update();

	sanguis::server::entities::with_buffs::update();

	sanguis::server::entities::with_health::update();

	sanguis::server::entities::with_velocity::update();
}

sanguis::server::team
sanguis::server::entities::friend_::team() const
{
	return sanguis::server::team::players;
}

sanguis::messages::server::unique_ptr
sanguis::server::entities::friend_::add_message(
	sanguis::server::player_id const,
	sanguis::collision::world::created const _created
) const
{
	return
		sanguis::messages::server::create_ptr(
			sanguis::messages::server::add_friend(
				sanguis::messages::roles::entity_id{} =
					this->id(),
				sanguis::messages::roles::center{} =
					this->center().get(),
				sanguis::messages::roles::angle{} =
					this->angle().get(),
				sanguis::messages::roles::created{} =
					_created.get(),
				sanguis::messages::roles::speed{} =
					this->speed().get(),
				sanguis::messages::roles::health{} =
					this->current_health().get(),
				sanguis::messages::roles::max_health{} =
					this->max_health().get(),
				sanguis::messages::roles::primary_weapon{} =
					this->primary_weapon_type(),
				sanguis::messages::roles::weapon_status{} =
					this->weapon_status(),
				sanguis::messages::roles::aura_type_container{} =
					this->aura_types(),
				sanguis::messages::roles::buff_type_container{} =
					this->buff_types(),
				sanguis::messages::roles::friend_type{} =
					friend_type_
			)
		);
}


sanguis::collision::world::body_group
sanguis::server::entities::friend_::collision_group() const
{
	return
		sanguis::collision::world::body_group::player;
}
