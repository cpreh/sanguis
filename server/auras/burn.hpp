#ifndef SANGUIS_SERVER_AURAS_BURN_HPP_INCLUDED
#define SANGUIS_SERVER_AURAS_BURN_HPP_INCLUDED

#include "aura.hpp"
#include "../space_unit.hpp"
#include "../damage/array.hpp"
#include "../../time_type.hpp"

namespace sanguis
{
namespace server
{
namespace auras
{

class burn : public aura {
public:
	burn(
		environment const &,
		space_unit radius,
		team::type team,
		space_unit damage_per_pules,
		time_type pulse_diff,
		damage::array const &);
private:
	void do_effect(
		entities::entity &target);
	
	time_type const pulse_diff;
	space_unit const damage_per_pulse;
	damage::array const damage_values;
};

}
}
}

#endif
