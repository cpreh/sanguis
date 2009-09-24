#include "entity_with_ai.hpp"
#include "../weapons/weapon.hpp"
#include "../ai/base.hpp"

sanguis::server::entities::entity_with_ai::~entity_with_ai()
{}

sanguis::server::entities::entity_with_ai::entity_with_ai(
	base_parameters const &param,
	ai::auto_ptr ai_,
	weapons::auto_ptr start_weapon)
:
	entity_with_weapon(
		param,
		start_weapon
	),
	ai_(ai_)
{
	this->ai_->bind(*this);
}

void
sanguis::server::entities::entity_with_ai::update(
	time_type const time
)
{
	entity_with_weapon::update(
		time
	);
	
	ai_->update(
		time
	);
}
