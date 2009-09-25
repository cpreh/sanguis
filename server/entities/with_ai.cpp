#include "entity_with_ai.hpp"
#include "../weapons/weapon.hpp"
#include "../ai/base.hpp"

sanguis::server::entities::entity_with_ai::entity_with_ai(
	ai::auto_ptr ai_,
	weapons::auto_ptr start_weapon)
:
	base(),
	with_weapon(
		start_weapon
	),
	ai_(ai_)
{
	this->ai_->bind(*this);
}

sanguis::server::entities::entity_with_ai::~entity_with_ai()
{}

void
sanguis::server::entities::entity_with_ai::on_update(
	time_type const time
)
{
	entity_with_weapon::on_update(
		time
	);
	
	ai_->update(
		time
	);
}
