#include "aura.hpp"
#include "../collision.hpp"
#include "../entities/entity.hpp"
#include <sge/math/circle_impl.hpp>

sanguis::server::auras::aura::~aura()
{}

void sanguis::server::auras::aura::pos(
	messages::pos_type const &p)
{
	circle_.origin() = p;
}

sanguis::server::auras::aura::aura(
	messages::circle_type const &circle_,
	team::type const team_,
	influence::type const influence_)
:
	circle_(circle_),
	team_(team_),
	influence_(influence_)
{}
