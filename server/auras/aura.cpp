#include "aura.hpp"
#include "../environment.hpp"
#include "../entities/entity.hpp"
#include <sge/collision/objects/circle.hpp>
#include <sge/math/circle_impl.hpp>
#include <sge/math/vector/construct.hpp>

sanguis::server::auras::aura::~aura()
{}

void sanguis::server::auras::aura::pos(
	messages::pos_type const &p)
{
	circle()->center(
		sge::math::vector::construct(
			p,
			static_cast<space_unit>(0)
		)
	);
}

sanguis::server::auras::aura::aura(
	environment const &env,
	messages::circle_type const &circle_,
	team::type const team_,
	influence::type const influence_)
:
	collision::base(
		env.collision(),
		circle_.origin(),
		pos_type::null(),
		circle_.radius()
	),
	team_(team_),
	influence_(influence_)
{}

bool
sanguis::server::auras::aura::can_collide_with(
	collision::base const &o) const
{
	entities::entity const *const entity(
		dynamic_cast<entities::entity const *>(&o)
	);

	return entity && (
			(entity->team() == team_ && influence_ == influence::buff)
			|| (entity->team() != team_ && influence_ == influence::debuff));
}


void
sanguis::server::auras::aura::collision(
	collision::base &b)
{
	do_effect(
		dynamic_cast<entities::entity &>(b)
	);
}
