#include "aura.hpp"
#include "../entities/entity.hpp"
#include "../collision/create_circle.hpp"
#include <sge/collision/objects/circle.hpp>
#include <sge/math/circle/basic_impl.hpp>
#include <sge/math/vector/construct.hpp>
#include <boost/logic/tribool.hpp>

sanguis::server::auras::aura::~aura()
{}

void
sanguis::server::auras::aura::center(
	pos_type const &p
)
{
	collision_object()->pos(
		sge::math::vector::construct(
			p,
			static_cast<space_unit>(0)
		)
	);
}

void
sanguis::server::auras::aura::owner(
	entity_id const nowner)
{
	owner_ = nowner;
}

sanguis::server::auras::aura::aura(
	sge::collision::world_ptr const collision_world_,
	space_unit const radius,
	team::type const team_,
	influence::type const influence_
)
:
	collision::base(
		collision::create_circle(
			collision_world_,
			pos_type::null(), // will be set later
			static_cast<space_unit>(0), // direction
			radius,
			static_cast<space_unit>(0), // movement speed
			*this
		)
	),
	team_(team_),
	influence_(influence_),
	owner_(static_cast<entity_id>(-1)) // will also be set later
{}

sanguis::entity_id
sanguis::server::auras::aura::owner() const
{
	return owner_;
}

boost::logic::tribool const
sanguis::server::auras::aura::can_collide_with(
	collision::base const &o) const
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
