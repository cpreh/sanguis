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
public:
	~with_ai();

	with_ai(
		base_parameters const &,
		ai::auto_ptr ai_,
		weapons::auto_ptr start_weapon
	);
protected:
	virtual void
	update(
		time_type
	);
private:
	ai::auto_ptr ai_;
};

}
}
}

#endif
