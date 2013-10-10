#ifndef SANGUIS_SERVER_BUFFS_BURN_HPP_INCLUDED
#define SANGUIS_SERVER_BUFFS_BURN_HPP_INCLUDED

#include <sanguis/diff_clock_fwd.hpp>
#include <sanguis/diff_timer.hpp>
#include <sanguis/duration.hpp>
#include <sanguis/server/buffs/buff.hpp>
#include <sanguis/server/damage/array.hpp>
#include <sanguis/server/damage/unit.hpp>
#include <sanguis/server/entities/base_fwd.hpp>
#include <fcppt/noncopyable.hpp>
#include <fcppt/strong_typedef.hpp>


namespace sanguis
{
namespace server
{
namespace buffs
{

class burn
:
	public sanguis::server::buffs::buff
{
	FCPPT_NONCOPYABLE(
		burn
	);
public:
	FCPPT_MAKE_STRONG_TYPEDEF(
		sanguis::server::damage::unit,
		damage_per_pulse
	);

	FCPPT_MAKE_STRONG_TYPEDEF(
		sanguis::duration,
		pulse_time
	);

	FCPPT_MAKE_STRONG_TYPEDEF(
		unsigned,
		max_pulses
	);

	burn(
		sanguis::diff_clock const &,
		sanguis::server::buffs::burn::damage_per_pulse,
		sanguis::server::buffs::burn::pulse_time const &,
		sanguis::server::buffs::burn::max_pulses,
		sanguis::server::damage::array const &
	);

	~burn();
private:
	void
	update(
		sanguis::server::entities::base &
	)
	override;

	sanguis::server::buffs::burn::damage_per_pulse const damage_per_pulse_;

	sanguis::diff_timer pulse_timer_;

	sanguis::server::buffs::burn::max_pulses::value_type pulses_;

	sanguis::server::buffs::burn::max_pulses const max_pulses_;

	sanguis::server::damage::array const damage_values_;
};

}
}
}

#endif
