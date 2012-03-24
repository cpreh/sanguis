#ifndef SANGUIS_SERVER_BUFFS_BURN_HPP_INCLUDED
#define SANGUIS_SERVER_BUFFS_BURN_HPP_INCLUDED

#include <sanguis/server/buffs/buff.hpp>
#include <sanguis/server/space_unit.hpp>
#include <sanguis/server/damage/array.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/duration.hpp>
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
	);
public:
	burn(
		sanguis::diff_clock const &,
		damage::unit,
		sanguis::duration const &pulse_time,
		unsigned max_pulses,
		damage::array const &
	);

	~burn();
private:
	void
	update(
		entities::base &
	);

	damage::unit const damage_;

	sanguis::diff_timer pulse_timer_;

	unsigned pulses_;

	unsigned const max_pulses_;

	damage::array const damage_values_;
};

}
}
}

#endif
