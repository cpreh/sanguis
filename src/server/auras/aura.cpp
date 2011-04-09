#include "aura.hpp"
#include "collision_groups.hpp"
#include "../collision/circle_ghost.hpp"
#include "../collision/ghost_unique_ptr.hpp"
#include "../entities/with_body.hpp"
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional_impl.hpp>
#include <boost/logic/tribool.hpp>

sanguis::server::auras::aura::~aura()
{
}

void
sanguis::server::auras::aura::owner(
	entity_id const _owner
)
{
	owner_ = _owner;
}

sanguis::server::collision::ghost_unique_ptr
sanguis::server::auras::aura::recreate()
{
	return
		collision::ghost_unique_ptr(
			fcppt::make_unique_ptr<
				collision::circle_ghost
			>(
				this->collision_groups(),
				radius_,
				this->body_enter_callback(),
				this->body_exit_callback()
			)
		);
}

sanguis::server::auras::aura::aura(
	server::radius const _radius,
	team::type const _team,
	influence::type const _influence
)
:
	radius_(_radius),
	team_(_team),
	influence_(_influence),
	owner_()
{
}

sanguis::entity_id
sanguis::server::auras::aura::owner() const
{
	return *owner_;
}

sanguis::server::collision::group_vector const
sanguis::server::auras::aura::collision_groups() const
{
	return
		auras::collision_groups(
			team_,
			influence_
		);
}

boost::logic::tribool const
sanguis::server::auras::aura::can_collide_with(
	collision::body_base const &
) const
{
	return true;
}

void
sanguis::server::auras::aura::body_enter(
	collision::body_base &_base
)
{
	this->enter(
		dynamic_cast<
			entities::with_body &
		>(
			_base
		)
	);
}

void
sanguis::server::auras::aura::body_exit(
	collision::body_base &_base
)
{
	this->leave(
		dynamic_cast<
			entities::with_body &
		>(
			_base
		)
	);
}
