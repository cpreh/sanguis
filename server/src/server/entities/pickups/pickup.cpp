#include <sanguis/diff_timer.hpp>
#include <sanguis/pickup_type.hpp>
#include <sanguis/collision/world/body_group.hpp>
#include <sanguis/collision/world/created.hpp>
#include <sanguis/load/model/pickup_path.hpp>
#include <sanguis/messages/roles/angle.hpp>
#include <sanguis/messages/roles/center.hpp>
#include <sanguis/messages/roles/created.hpp>
#include <sanguis/messages/roles/entity_id.hpp>
#include <sanguis/messages/roles/pickup_type.hpp>
#include <sanguis/messages/server/add_pickup.hpp>
#include <sanguis/messages/server/base.hpp>
#include <sanguis/messages/server/create_ptr.hpp>
#include <sanguis/messages/server/unique_ptr.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/optional_mass.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/entities/player.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/with_id.hpp>
#include <sanguis/server/entities/with_links.hpp>
#include <sanguis/server/entities/pickups/pickup.hpp>
#include <sanguis/server/environment/load_context.hpp>
#include <alda/message/init_record.hpp>
#include <fcppt/const.hpp>
#include <fcppt/reference_impl.hpp>
#include <fcppt/cast/dynamic.hpp>
#include <fcppt/optional/maybe.hpp>
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
	sanguis::server::entities::with_body(
		_load_context.model_size(
			sanguis::load::model::pickup_path(
				_pickup_type
			)
		),
		sanguis::server::optional_mass()
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
	return
		life_timer_.expired();
}

sanguis::server::team
sanguis::server::entities::pickups::pickup::team() const
{
	return
		team_;
}

boost::logic::tribool
sanguis::server::entities::pickups::pickup::can_collide_with_body(
	sanguis::server::entities::with_body const &_body
) const
{
	return
		fcppt::optional::maybe(
			fcppt::cast::dynamic<
				sanguis::server::entities::player const
			>(
				_body
			),
			fcppt::const_(
				false
			),
			[
				this
			](
				fcppt::reference<
					sanguis::server::entities::player const
				> const _player
			)
			{
				return
					_player.get().team()
					==
					this->team();
			}
		);
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

	if(
		this->do_pickup(
			_body
		)
	)
		life_timer_.expired(
			true
		);
}

sanguis::collision::world::body_group
sanguis::server::entities::pickups::pickup::collision_group() const
{
	return
		sanguis::collision::world::body_group::pickup;
}

sanguis::messages::server::unique_ptr
sanguis::server::entities::pickups::pickup::add_message(
	sanguis::server::player_id const,
	sanguis::collision::world::created const _created
) const
{
	return
		sanguis::messages::server::create_ptr(
			alda::message::init_record<
				sanguis::messages::server::add_pickup
			>(
				sanguis::messages::roles::entity_id{} =
					this->id(),
				sanguis::messages::roles::center{} =
					this->center().get(),
				sanguis::messages::roles::angle{} =
					this->angle().get(),
				sanguis::messages::roles::created{} =
					_created.get(),
				sanguis::messages::roles::pickup_type{} =
					pickup_type_
			)
		);
}
