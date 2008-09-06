#ifndef SANGUIS_SERVER_ENTITIES_SENTRY_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_SENTRY_HPP_INCLUDED

#include "entity_with_ai.hpp"
#include "../ai/base.hpp"

namespace sanguis
{
namespace server
{
namespace entities
{

class sentry : public entity_with_ai {
public:
	sentry(
		environment const &,
		armor_array const &,
		messages::pos_type const &pos,
		messages::space_unit angle,
		messages::space_unit direction,
		property_map const &,
		ai::ai_ptr,
		team::type team_,
		weapons::weapon_ptr weapon);
private:
	entity_type::type type() const;
	messages::dim_type const dim() const;
	bool invulnerable() const;
};

}
}
}

#endif
