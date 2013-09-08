#include <sanguis/collision/world/body_base.hpp>
#include <sanguis/collision/world/group_field.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/auras/aura.hpp>
#include <sanguis/server/auras/collision_groups.hpp>
#include <sanguis/server/auras/influence.hpp>
#include <sanguis/server/collision/ghost.hpp>
#include <sanguis/server/collision/ghost_base.hpp>
#include <sanguis/server/collision/ghost_unique_ptr.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/logic/tribool.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::server::auras::aura::~aura()
{
}

sanguis::server::collision::ghost_unique_ptr
sanguis::server::auras::aura::create_ghost()
{
	return
		sanguis::server::collision::ghost_unique_ptr(
			fcppt::make_unique_ptr<
				sanguis::server::collision::ghost
			>(
				this->collision_groups(),
				this->body_enter_callback(),
				this->body_exit_callback(),
				radius_
			)
		);
}

sanguis::server::auras::aura::aura(
	sanguis::server::radius const _radius,
	sanguis::server::team const _team,
	sanguis::server::auras::influence const _influence
)
:
	sanguis::server::collision::ghost_base(),
	radius_(
		_radius
	),
	team_(
		_team
	),
	influence_(
		_influence
	)
{
}

sanguis::collision::world::group_field const
sanguis::server::auras::aura::collision_groups() const
{
	return
		sanguis::server::auras::collision_groups(
			team_,
			influence_
		);
}

boost::logic::tribool const
sanguis::server::auras::aura::can_collide_with(
	sanguis::collision::world::body_base const &
) const
{
	return true;
}

void
sanguis::server::auras::aura::body_enter(
	sanguis::collision::world::body_base &_base
)
{
	this->enter(
		dynamic_cast<
			sanguis::server::entities::with_body &
		>(
			_base
		)
	);
}

void
sanguis::server::auras::aura::body_exit(
	sanguis::collision::world::body_base &_base
)
{
	this->leave(
		dynamic_cast<
			sanguis::server::entities::with_body &
		>(
			_base
		)
	);
}
