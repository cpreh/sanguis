#ifndef SANGUIS_SERVER_ENTITIES_ENTITY_WITH_AI_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_ENTITY_WITH_AI_HPP_INCLUDED

#include "entity_with_weapon.hpp"
#include "../ai/auto_ptr.hpp"

namespace sanguis
{
namespace server
{
namespace entities
{

class entity_with_ai : public entity_with_weapon {
public:
	~entity_with_ai();

	entity_with_ai(
		base_parameters const &,
		ai::auto_ptr ai_,
		weapons::auto_ptr start_weapon);
protected:
	virtual void update(
		time_type,
		container &entities);
private:
	ai::auto_ptr ai_;
};

}
}
}

#endif
