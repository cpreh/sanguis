#ifndef SANGUIS_SERVER_BUFFS_BURN_HPP_INCLUDED
#define SANGUIS_SERVER_BUFFS_BURN_HPP_INCLUDED

#include "../space_unit.hpp"
#include "../damage/array.hpp"
#include "../damage/unit.hpp"
#include "../../diff_clock.hpp"
#include "../../time_type.hpp"
#include "buff.hpp"
#include <sge/time/timer.hpp>
#include <fcppt/noncopyable.hpp>

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
	FCPPT_NONCOPYABLE(
		burn
	)
public:
	burn(
		damage::unit,
		time_type pulse_time,
		unsigned max_pulses,
		damage::array const &
	);

	~burn();
private:
	void
	update(
		entities::base &,
		time_type
	);

	damage::unit const damage_;

	diff_clock clock_;

	sge::time::timer pulse_timer_;

	unsigned pulses_;

	unsigned const max_pulses_;

	damage::array const damage_values_;
};

}
}
}

#endif
