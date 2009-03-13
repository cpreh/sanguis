#ifndef SANGUIS_SERVER_BUFFS_BURN_HPP_INCLUDED
#define SANGUIS_SERVER_BUFFS_BURN_HPP_INCLUDED

#include "../types.hpp"
#include "../../diff_clock.hpp"
#include "../../time_type.hpp"
#include "../../damage_type.hpp"
#include "buff.hpp"
#include <sge/time/timer.hpp>

namespace sanguis
{
namespace server
{
namespace buffs
{

class burn : public buff {
public:
	burn(
		entity_id source,
		space_unit damage,
		time_type pulse_time,
		unsigned max_pulses,
		damage_array const &);
private:
	void update(
		entities::entity &,
		time_type);

	space_unit const damage;
	diff_clock clock_;
	sge::time::timer pulse_timer;
	unsigned pulses;
	unsigned const max_pulses;
	damage_array const damage_values;
};

}
}
}

#endif
