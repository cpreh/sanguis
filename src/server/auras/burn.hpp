#ifndef SANGUIS_SERVER_AURAS_BURN_HPP_INCLUDED
#define SANGUIS_SERVER_AURAS_BURN_HPP_INCLUDED

#include "aura.hpp"
#include "../buffs/provider.hpp"
#include "../damage/array.hpp"
#include "../damage/unit.hpp"
#include "../space_unit.hpp"
#include "../../time_type.hpp"
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace auras
{

class burn
:
	public aura
{
	FCPPT_NONCOPYABLE(
		burn
	);
public:
	burn(
		space_unit radius,
		team::type team,
		damage::unit damage_per_pules,
		time_type pulse_diff,
		damage::array const &
	);

	~burn();
private:
	void
	enter(
		entities::base &target
	);

	void
	leave(
		entities::base &target
	);
	
	time_type const pulse_diff_;

	damage::unit const damage_per_pulse_;

	damage::array const damage_values_;

	buffs::provider provider_;
};

}
}
}

#endif
