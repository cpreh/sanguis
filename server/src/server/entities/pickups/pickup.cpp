#include <sanguis/diff_timer.hpp>
#include <sanguis/pickup_type.hpp>
#include <sanguis/collision/world/group.hpp>
#include <sanguis/collision/world/group_field.hpp>
#include <sanguis/load/pickup_name.hpp>
#include <sanguis/messages/roles/angle.hpp>
#include <sanguis/messages/roles/center.hpp>
#include <sanguis/messages/roles/entity_id.hpp>
#include <sanguis/messages/roles/pickup_type.hpp>
#include <sanguis/messages/server/add_pickup.hpp>
#include <sanguis/messages/server/create_ptr.hpp>
#include <sanguis/messages/server/unique_ptr.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/model_name.hpp>
#include <sanguis/server/model_size.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/entities/player.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/entities/with_links.hpp>
#include <sanguis/server/entities/ifaces/with_team.hpp>
#include <sanguis/server/entities/pickups/pickup.hpp>
#include <sanguis/server/environment/load_context.hpp>
#include <fcppt/try_dynamic_cast.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/logic/tribool.hpp>
#include <chrono>
#include <fcppt/config/external_end.hpp>


sanguis::server::entities::pickups::pickup::~pickup()
{
}

sanguis::server::entities::pickups::pickup::pickup(
	sanguis::pickup_type const _pickup_type,
	sanguis::server::environment::load_context &_load_context,
	sanguis::server::team const _team
)
:
	sanguis::server::entities::ifaces::with_team(),
	sanguis::server::entities::with_body(
		_load_context.model_size(
			sanguis::server::model_name(
				sanguis::load::pickup_name(
					_pickup_type
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
	pickup_type_(
		_pickup_type
	),
	life_timer_(
		sanguis::diff_timer::parameters(
			this->diff_clock(),
			std::chrono::seconds(
				30
			)
		)
	)
{
}

bool
sanguis::server::entities::pickups::pickup::dead() const
{
	return life_timer_.expired();
}

sanguis::server::team
sanguis::server::entities::pickups::pickup::team() const
{
	return team_;
}

boost::logic::tribool const
sanguis::server::entities::pickups::pickup::can_collide_with_body(
	sanguis::server::entities::with_body const &_body
) const
{
	FCPPT_TRY_DYNAMIC_CAST(
		sanguis::server::entities::player const *,
		player,
		&_body
	)
	{
		return
			player->team() == this->team();
	}

	return
		false;
}

void
sanguis::server::entities::pickups::pickup::collision_with_body(
	sanguis::server::entities::with_body &_body
)
{
	// if something is spawned by this pickup that can pickup entities itself
	// we will get an endless loop
	if(
		this->dead()
	)
		return;

	life_timer_.expired(
		true
	);

	this->do_pickup(
		_body
	);
}

sanguis::collision::world::group_field const
sanguis::server::entities::pickups::pickup::collision_groups() const
{
	return
		sanguis::collision::world::group_field{
			sanguis::collision::world::group::pickup
		};
}

sanguis::messages::server::unique_ptr
sanguis::server::entities::pickups::pickup::add_message(
	sanguis::server::player_id const
) const
{
	return
		sanguis::messages::server::create_ptr(
			sanguis::messages::server::add_pickup(
				sanguis::messages::roles::entity_id{} =
					this->id(),
				sanguis::messages::roles::center{} =
					this->center().get(),
				sanguis::messages::roles::angle{} =
					this->angle().get(),
				sanguis::messages::roles::pickup_type{} =
					pickup_type_
			)
		);
}
