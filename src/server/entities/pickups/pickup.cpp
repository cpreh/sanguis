#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/entity_type.hpp>
#include <sanguis/pickup_type.hpp>
#include <sanguis/load/pickup_name.hpp>
#include <sanguis/messages/add_pickup.hpp>
#include <sanguis/messages/create.hpp>
#include <sanguis/messages/unique_ptr.hpp>
#include <sanguis/messages/types/enum.hpp>
#include <sanguis/server/center.hpp>
#include <sanguis/server/player_id.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/entities/base.hpp>
#include <sanguis/server/entities/circle_from_dim.hpp>
#include <sanguis/server/entities/nonsolid.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <sanguis/server/entities/pickups/optional_dim.hpp>
#include <sanguis/server/entities/pickups/pickup.hpp>
#include <sanguis/server/environment/load_context.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/chrono/duration.hpp>
#include <boost/logic/tribool.hpp>
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
	sanguis::server::team const _team,
	sanguis::server::entities::pickups::optional_dim const &_dim
)
:
	sanguis::server::entities::base(),
	sanguis::server::entities::with_body(
		sanguis::server::entities::circle_from_dim(
			_dim
			?
				*_dim
			:
				_load_context.entity_dim(
					sanguis::load::pickup_name(
						_ptype
					)
				),
			sanguis::server::entities::nonsolid()
		)
	),
	team_(
		_team
	),
	ptype_(
		_ptype
	),
	life_timer_(
		sanguis::diff_timer::parameters(
			_diff_clock,
			boost::chrono::seconds(
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

sanguis::entity_type
sanguis::server::entities::pickups::pickup::type() const
{
	return entity_type::pickup;
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
	return
		_body.team() == this->team()
		&& _body.type() == sanguis::entity_type::player;
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
				static_cast<
					sanguis::messages::types::enum_
				>(
					this->ptype()
				)
			)
		);
}
