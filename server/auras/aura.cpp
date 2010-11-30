#include "aura.hpp"
#include "collision_groups.hpp"
#include "../collision/assign_groups.hpp"
#include "../collision/create_circle.hpp"
#include "../entities/base.hpp"
#include <fcppt/assign/make_container.hpp>
#include <boost/logic/tribool.hpp>

sanguis::server::auras::aura::~aura()
{}

void
sanguis::server::auras::aura::owner(
	entity_id const _owner
)
{
	owner_ = _owner;
}

sge::collision::shapes::container const
sanguis::server::auras::aura::recreate_shapes(
	sge::collision::world_ptr const _world,
	collision::global_groups const &_global_groups
)
{
	return 
		collision::assign_groups(
			fcppt::assign::make_container<
				sge::collision::shapes::container
			>(
				collision::create_circle(
					_world,
					*this,
					radius_
				)
			),
			collision_groups(),
			_global_groups
		);
}

sanguis::server::auras::aura::aura(
	space_unit const _radius,
	team::type const _team,
	influence::type const _influence
)
:
	collision::base(),
	radius_(_radius),
	team_(_team),
	influence_(_influence),
	owner_(
		static_cast<entity_id>(-1)
	) // will also be set later
{}

sanguis::entity_id
sanguis::server::auras::aura::owner() const
{
	return owner_;
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
	collision::base const &_object
) const
{
	entities::base const *const entity(
		dynamic_cast<
			entities::base const *
		>(
			&_object
		)
	);

	return
		entity
		&& !entity->server_only();
}

void
sanguis::server::auras::aura::collision_begin(
	collision::base &_base
)
{
	enter(
		dynamic_cast<
			entities::base &
		>(
			_base
		)
	);
}

void
sanguis::server::auras::aura::collision_end(
	collision::base &_base
)
{
	leave(
		dynamic_cast<
			entities::base &
		>(
			_base
		)
	);
}
