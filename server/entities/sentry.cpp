#include "sentry.hpp"
#include "../get_dim.hpp"
#include <sge/text.hpp>

sanguis::server::entities::sentry::sentry(
	environment const &env,
	armor_array const &armor_,
	messages::pos_type const &pos,
	messages::space_unit angle,
	messages::space_unit direction,
	property_map const &properties,
	ai::ai_ptr ai_,
	team::type const team_,
	weapons::weapon_ptr weapon_)
:
	entity_with_ai(
		env,
		armor_,
		pos,
		angle,
		direction,
		team_,
		properties,
		ai_,
		weapon_)
{}

sanguis::entity_type::type
sanguis::server::entities::sentry::type() const
{
	return entity_type::sentry;
}

sanguis::messages::dim_type const
sanguis::server::entities::sentry::dim() const
{
	return get_dim(
		SGE_TEXT("sentry"),
		SGE_TEXT("default"));
}

bool sanguis::server::entities::sentry::invulnerable() const
{
	return false;
}
