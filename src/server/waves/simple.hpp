#ifndef SANGUIS_SERVER_WAVES_SIMPLE_HPP_INCLUDED
#define SANGUIS_SERVER_WAVES_SIMPLE_HPP_INCLUDED

#include "wave.hpp"
#include "../environment/load_context_fwd.hpp"
#include "../environment/object_fwd.hpp"
#include "../../time_type.hpp"
#include "../../enemy_type.hpp"
#include "../../diff_clock.hpp"
#include <sge/time/timer.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace waves
{

class simple
:
	public wave
{
	FCPPT_NONCOPYABLE(
		simple
	);
public:
	simple(
		time_type delay,
		time_type spawn_interval,
		unsigned waves,
		unsigned spawns_per_wave,
		enemy_type::type
	);

	~simple();
private:
	void
	process(
		time_type diff,
		environment::object &,
		environment::load_context &
	);

	bool
	ended() const;

	diff_clock diff_;

	sge::time::timer
		delay_timer_,
		spawn_timer_;

	unsigned const
		waves_,
		spawns_per_wave_;

	enemy_type::type const etype_;

	unsigned waves_spawned_;
};

}
}
}

#endif
