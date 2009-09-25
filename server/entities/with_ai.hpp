#ifndef SANGUIS_SERVER_ENTITIES_WITH_AI_HPP_INCLUDED
#define SANGUIS_SERVER_ENTITIES_WITH_AI_HPP_INCLUDED

#include "with_weapon.hpp"
#include "../ai/auto_ptr.hpp"

namespace sanguis
{
namespace server
{
namespace entities
{

class with_ai
:
	public with_weapon
{
protected:
	with_ai(
		ai::auto_ptr ai_,
		weapons::auto_ptr start_weapon
	);

	~with_ai();

	virtual void
	on_update(
		time_type
	);
private:
	ai::auto_ptr ai_;
};

}
}
}

#endif
