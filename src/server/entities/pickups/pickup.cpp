#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/pickup_type.hpp>
#include <sanguis/collision/world/group.hpp>
#include <sanguis/collision/world/group_field.hpp>
#include <sanguis/load/pickup_name.hpp>
#include <sanguis/messages/add_pickup.hpp>
#include <sanguis/messages/create.hpp>
#include <sanguis/messages/unique_ptr.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/dim.hpp>
#include <sanguis/server/model_name.hpp>
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


sanguis::pickup_type
sanguis::server::entities::pickups::pickup::ptype() const
{
	return ptype_;
}

sanguis::server::entities::pickups::pickup::~pickup()
{
}

sanguis::server::entities::pickups::pickup::pickup(
	sanguis::diff_clock const &_diff_clock,
	sanguis::pickup_type const _ptype,
	sanguis::server::environment::load_context &_load_context,
	sanguis::server::team const _team
)
:
	sanguis::server::entities::ifaces::with_team(),
	sanguis::server::entities::with_body(
		_diff_clock,
		_load_context.entity_dim(
			sanguis::server::model_name(
				sanguis::load::pickup_name(
					_ptype
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
	ptype_(
		_ptype
	),
	life_timer_(
		sanguis::diff_timer::parameters(
			_diff_clock,
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

sanguis::messages::unique_ptr
sanguis::server::entities::pickups::pickup::add_message(
	sanguis::server::player_id const
) const
{
	return
		sanguis::messages::create(
			sanguis::messages::add_pickup(
				this->id(),
				this->center().get(),
				this->angle().get(),
				this->ptype()
			)
		);
}
