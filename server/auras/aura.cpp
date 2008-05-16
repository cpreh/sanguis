#include "aura.hpp"
#include "../collision.hpp"
#include "../entities/entity.hpp"
#include <boost/foreach.hpp>

sanguis::server::auras::aura::~aura()
{}

sanguis::server::auras::aura::aura(
	messages::circle_type const &circle_,
	const team::type team_,
	const influence::type influence_)
: circle_(circle_),
  team_(team_),
  influence_(influence_)
{}

void sanguis::server::auras::aura::update(
	time_type,
	entities::container &entities)
{
	BOOST_FOREACH(entities::entity &e, entities)
		if(((influence_ == influence::buff
			&& e.team() == team_)
		|| (influence_ == influence::debuff
			&& e.team() != team_))
		&& collides(e, circle_))
			do_effect(e);
}
