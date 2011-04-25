#include "pickup.hpp"
#include "../circle_from_dim.hpp"
#include "../nonsolid.hpp"
#include "../../environment/load_context.hpp"
#include "../../../load/pickup_name.hpp"
#include "../../../messages/add_pickup.hpp"
#include "../../../messages/create.hpp"
#include <fcppt/math/vector/basic_impl.hpp>
#include <fcppt/math/dim/basic_impl.hpp>
#include <sge/time/second.hpp>
#include <fcppt/container/map_impl.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/text.hpp>
#include <boost/logic/tribool.hpp>

sanguis::pickup_type::type
sanguis::server::entities::pickups::pickup::ptype() const
{
	return ptype_;
}

sanguis::server::entities::pickups::pickup::~pickup()
{
}

sanguis::server::entities::pickups::pickup::pickup(
	pickup_type::type const _ptype,
	server::environment::load_context &_load_context,
	team::type const _team,
	optional_dim const &_dim
)
:
	base(),
	with_body(
		entities::circle_from_dim(
			_dim
			?
				*_dim
			:
				_load_context.entity_dim(
					load::pickup_name(
						_ptype
					)
				),
			entities::nonsolid()
		)
	),
	team_(_team),
	ptype_(_ptype),
	diff_clock_(),
	life_timer_(
		sge::time::second(
			30
		),
		sge::time::activation_state::active,
		diff_clock_.callback()
	)
{
}

bool
sanguis::server::entities::pickups::pickup::dead() const
{
	return life_timer_.expired();
}

sanguis::entity_type::type
sanguis::server::entities::pickups::pickup::type() const
{
	return entity_type::pickup;
}

sanguis::server::team::type
sanguis::server::entities::pickups::pickup::team() const
{
	return team_;
}

boost::logic::tribool const
sanguis::server::entities::pickups::pickup::can_collide_with_body(
	entities::with_body const &_body
) const
{
	return
		_body.team() == this->team()
		&& _body.type() == entity_type::player;
}

void
sanguis::server::entities::pickups::pickup::collision_with_body(
	entities::with_body &_body
)
{
	// if something is spawned by this pickup that can pickup entities itself
	// we will get an endless loop
	if(
		this->dead()
	)
		return;
	
	life_timer_.expire();

	this->do_pickup(
		_body
	);
}

void
sanguis::server::entities::pickups::pickup::on_update(
	sanguis::time_delta const &_time
)
{
	diff_clock_.update(
		_time
	);
}

sanguis::messages::auto_ptr
sanguis::server::entities::pickups::pickup::add_message(
	player_id const
) const
{
	return
		messages::create(
			messages::add_pickup(
				this->id(),
				this->center().get(),
				this->angle().get(),
				this->ptype()
			)
		);
}
