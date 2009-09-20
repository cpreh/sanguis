#include "aura.hpp"
#include "../entities/entity.hpp"
#include <sge/collision/shapes/circle.hpp>
#include <sge/collision/body.hpp>
#include <sge/collision/world.hpp>
#include <sge/math/circle/basic_impl.hpp>
#include <sge/math/vector/construct.hpp>
#include <sge/assign/make_container.hpp>
#include <boost/logic/tribool.hpp>

sanguis::server::auras::aura::~aura()
{}

void
sanguis::server::auras::aura::center(
	pos_type const &p
)
{
	body()->position(
		sge::math::vector::construct(
			p,
			static_cast<space_unit>(0)
		)
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
	owner_(static_cast<entity_id>(-1)) // will also be set later
{}

sanguis::entity_id
sanguis::server::auras::aura::owner() const
{
	return owner_;
}

sanguis::server::collision::shape_vector const
sanguis::server::auras::aura::recreate_shapes(
	sge::collision::world_ptr const world_
) const
{
	return 
		sge::assign::make_container<
			collision::shape_vector
		>(
			world_->create_circle(
				radius_
			)
		);
	
}

boost::logic::tribool const
sanguis::server::auras::aura::can_collide_with(
	collision::base const &o
) const
{
	entities::entity const *const entity(
		dynamic_cast<entities::entity const *>(&o)
	);

	return
		entity
		&& (
			(
				entity->team() == team_
				&& influence_ == influence::buff
			)
			|| (
				entity->team() != team_
				&& influence_ == influence::debuff
			)
		);
}

void
sanguis::server::auras::aura::collision(
	collision::base &b
)
{
	do_effect(
		dynamic_cast<entities::entity &>(b)
	);
}
