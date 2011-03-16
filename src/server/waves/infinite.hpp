#ifndef SANGUIS_SERVER_WAVES_INFINITE_HPP_INCLUDED
#define SANGUIS_SERVER_WAVES_INFINITE_HPP_INCLUDED

#include "wave.hpp"
#include "delay.hpp"
#include "spawn_interval.hpp"
#include "spawns_per_wave.hpp"
#include "../../diff_clock.hpp"
#include "../../enemy_type.hpp"
#include "../../time_type.hpp"
#include <sge/time/timer.hpp>
#include <fcppt/noncopyable.hpp>

namespace sanguis
{
namespace server
{
namespace waves
{

class infinite
:
	public wave
{
	FCPPT_NONCOPYABLE(
		infinite
	);
public:
	infinite(
		waves::delay,
		waves::spawn_interval,
		waves::spawns_per_wave,
		enemy_type::type
	);
	
	~infinite();
private:
	void
	process(
		time_type diff,
		environment::object_ptr,
		environment::load_context_ptr
	);
	
	bool
	ended() const;

	diff_clock diff_clock_;
	
	sge::time::timer delay_time_;

	spawn_interval const spawn_interval_;

	spawns_per_wave const spawns_per_wave_;

	enemy_type::type const etype_;
};

}
}
}

#endif
