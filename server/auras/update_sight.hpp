#ifndef SANGUIS_SERVER_AURAS_UPDATE_SIGHT_HPP_INCLUDED
#define SANGUIS_SERVER_AURAS_UPDATE_SIGHT_HPP_INCLUDED

#include "aura.hpp"
#include "../space_unit.hpp"
#include "../update_sight_function.hpp"
#include "../entities/entity_fwd.hpp"

namespace sanguis
{
namespace server
{
namespace auras
{

class update_sight
:
	public aura
{
public:
	update_sight(
		space_unit radius,
		update_sight_function const &enter_,
		update_sight_function const &leave_
	);
private:
	void
	enter(
		entities::entity &target
	);

	void
	leave(
		entities::entity &target
	);

	update_sight_function const
		enter_,
		leave_;
};

}
}
}

#endif
