#include "aura.hpp"
#include "collision_groups.hpp"
#include "../collision/circle_ghost.hpp"
#include "../collision/ghost_unique_ptr.hpp"
#include "../entities/with_body.hpp"
#include <fcppt/tr1/functional.hpp>
#include <fcppt/make_unique_ptr.hpp>
#include <fcppt/optional_impl.hpp>

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
sanguis::server::auras::aura::recreate(
	collision::ghost_parameters const &_params,
	server::center const &_center
)
{
	return
		collision::ghost_unique_ptr(
			fcppt::make_unique_ptr<
				collision::circle_ghost
			>(
				_params,
				_center,
				radius_,
				std::tr1::bind(
					&aura::collision_begin,
					this,
					std::tr1::placeholders::_1
				),
				std::tr1::bind(
					&aura::collision_end,
					this,
					std::tr1::placeholders::_1
				)
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

void
sanguis::server::auras::aura::collision_begin(
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
sanguis::server::auras::aura::collision_end(
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
