#include <sanguis/entity_id.hpp>
#include <sanguis/server/radius.hpp>
#include <sanguis/server/team.hpp>
#include <sanguis/server/auras/aura.hpp>
#include <sanguis/server/auras/collision_groups.hpp>
#include <sanguis/server/auras/influence.hpp>
#include <sanguis/server/collision/circle_ghost.hpp>
#include <sanguis/server/collision/ghost_base.hpp>
#include <sanguis/server/collision/ghost_unique_ptr.hpp>
#include <sanguis/server/collision/group_vector.hpp>
#include <sanguis/server/entities/with_body.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/logic/tribool.hpp>
#include <fcppt/config/external_end.hpp>


sanguis::server::auras::aura::~aura()
{
}

void
sanguis::server::auras::aura::owner(
	sanguis::entity_id const _owner
)
{
	owner_ = _owner;
}

sanguis::server::collision::ghost_unique_ptr
sanguis::server::auras::aura::recreate()
{
	return
		sanguis::server::collision::ghost_unique_ptr(
			fcppt::make_unique_ptr<
				sanguis::server::collision::circle_ghost
			>(
				this->collision_groups(),
				radius_,
				this->body_enter_callback(),
				this->body_exit_callback()
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
	),
	owner_()
{
}

sanguis::entity_id const
sanguis::server::auras::aura::owner() const
{
	return *owner_;
}

sanguis::server::collision::group_vector const
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
	sanguis::server::collision::body_base const &
) const
{
	return true;
}

void
sanguis::server::auras::aura::body_enter(
	sanguis::server::collision::body_base &_base
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
	sanguis::server::collision::body_base &_base
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
