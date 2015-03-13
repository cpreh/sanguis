#include <sanguis/collision/world/body_base.hpp>
#include <sanguis/collision/world/created.hpp>
#include <sanguis/collision/world/ghost_group.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/auras/aura.hpp>
#include <sanguis/server/collision/ghost.hpp>
#include <sanguis/server/collision/ghost_base.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <fcppt/cast/static_downcast.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/logic/tribool.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::server::auras::aura::~aura()
{
}

sanguis::server::collision::ghost
sanguis::server::auras::aura::create_ghost()
{
	return
		sanguis::server::collision::ghost{
			collision_group_,
			*this,
			this->body_enter_callback(),
			this->body_exit_callback(),
			radius_
		};
}

sanguis::server::auras::aura::aura(
	sanguis::server::radius const _radius,
	sanguis::collision::world::ghost_group const _collision_group
)
:
	sanguis::server::collision::ghost_base(),
	radius_(
		_radius
	),
	collision_group_(
		_collision_group
	)
{
}

boost::logic::tribool const
sanguis::server::auras::aura::can_collide_with(
	sanguis::collision::world::body_base const &
) const
{
	return
		true;
}

void
sanguis::server::auras::aura::body_enter(
	sanguis::collision::world::body_base &_base,
	sanguis::collision::world::created const _created
)
{
	this->enter(
		fcppt::cast::static_downcast<
			sanguis::server::entities::with_body &
		>(
			_base
		),
		_created
	);
}

void
sanguis::server::auras::aura::body_exit(
	sanguis::collision::world::body_base &_base
)
{
	this->leave(
		fcppt::cast::static_downcast<
			sanguis::server::entities::with_body &
		>(
			_base
		)
	);
}
