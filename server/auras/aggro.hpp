#ifndef SANGUIS_SERVER_AURAS_AGGRO_HPP_INCLUDED
#define SANGUIS_SERVER_AURAS_AGGRO_HPP_INCLUDED

#include "aura.hpp"
#include "../space_unit.hpp"
#include "../team.hpp"
#include "../update_target_function.hpp"

namespace sanguis
{
namespace server
{
namespace auras
{

class aggro
:
	public aura
{
public:
	aggro(
		space_unit radius,
		team::type,
		update_target_function const &
	);
private:
	void
	do_effect(
		entities::entity &target
	);

	update_target_function const update_target_;
};


}
}
}

#endif
