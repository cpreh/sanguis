#ifndef SANGUIS_SERVER_BUFFS_BURN_HPP_INCLUDED
#define SANGUIS_SERVER_BUFFS_BURN_HPP_INCLUDED

#include "../space_unit.hpp"
#include "../damage/array.hpp"
#include "../damage/unit.hpp"
#include "../../diff_clock.hpp"
#include "../../time_type.hpp"
#include "buff.hpp"
#include <sge/time/timer.hpp>

namespace sanguis
{
namespace server
{
namespace buffs
{

class burn
:
	public buff
{
public:
	burn(
		entity_id source,
		damage::unit,
		time_type pulse_time,
		unsigned max_pulses,
		damage::array const &
	);
private:
	void
	update(
		entities::base &,
		time_type
	);

	damage::unit const damage_;
	diff_clock clock_;
	sge::time::timer pulse_timer;
	unsigned pulses;
	unsigned const max_pulses;
	damage::array const damage_values;
};

}
}
}

#endif
