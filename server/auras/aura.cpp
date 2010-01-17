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
	entity_id const nowner
)
{
	owner_ = nowner;
}

sge::collision::shapes::container const
sanguis::server::auras::aura::recreate_shapes(
	sge::collision::world_ptr const world_,
	collision::global_groups const &global_groups_
)
{
	return 
		collision::assign_groups(
			fcppt::assign::make_container<
				sge::collision::shapes::container
			>(
				collision::create_circle(
					world_,
					*this,
					radius_
				)
			),
			collision_groups(),
			global_groups_
		);
}

sanguis::server::auras::aura::aura(
	space_unit const radius_,
	team::type const team_,
	influence::type const influence_
)
:
	collision::base(),
	radius_(radius_),
	team_(team_),
	influence_(influence_),
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
	collision::base const &o
) const
{
	entities::base const *const entity_(
		dynamic_cast<
			entities::base const *
		>(&o)
	);

	return
		entity_
		&& !entity_->server_only();
}

void
sanguis::server::auras::aura::collision_begin(
	collision::base &b
)
{
	enter(
		dynamic_cast<entities::base &>(b)
	);
}

void
sanguis::server::auras::aura::collision_end(
	collision::base &b
)
{
	leave(
		dynamic_cast<entities::base &>(b)
	);
}
