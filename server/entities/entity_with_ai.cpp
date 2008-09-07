#include "entity_with_ai.hpp"

sanguis::server::entities::entity_with_ai::entity_with_ai(
	base_parameters const &param,
	ai::ai_ptr const ai_,
	weapons::weapon_ptr start_weapon)
:
	entity_with_weapon(
		param,
		start_weapon),
	ai_(ai_)
{}

void sanguis::server::entities::entity_with_ai::update(
	time_type const time,
	container &entities)
{
	entity_with_weapon::update(
		time,
		entities);
	
	ai_->update(
		*this,
		time,
		entities);
}
