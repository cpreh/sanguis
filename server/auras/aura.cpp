#include "aura.hpp"
#include "collision_groups.hpp"
#include "../entities/base.hpp"
#include <sge/collision/shapes/circle.hpp>
#include <sge/collision/body.hpp>
#include <sge/collision/world.hpp>
#include <sge/math/circle/basic_impl.hpp>
#include <sge/assign/make_container.hpp>
#include <sge/optional_impl.hpp>
#include <boost/logic/tribool.hpp>

sanguis::server::auras::aura::~aura()
{}

void
sanguis::server::auras::aura::center(
	pos_type const &p
)
{
	body_pos(
		p
	);
}

void
sanguis::server::auras::aura::owner(
	entity_id const nowner
)
{
	owner_ = nowner;
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

sge::collision::shapes::container const
sanguis::server::auras::aura::recreate_shapes(
	sge::collision::world_ptr const world_
) const
{
	return 
		sge::assign::make_container<
			sge::collision::shapes::container
		>(
			world_->create_circle(
				radius_
			)
		);
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
		&& entity_->type() != entity_type::indeterminate;
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
