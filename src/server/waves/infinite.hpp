#ifndef SANGUIS_SERVER_WAVES_INFINITE_HPP_INCLUDED
#define SANGUIS_SERVER_WAVES_INFINITE_HPP_INCLUDED

#include "wave.hpp"
#include "delay.hpp"
#include "spawn_interval.hpp"
#include "spawns_per_wave.hpp"
#include "../environment/load_context_fwd.hpp"
#include "../environment/object_fwd.hpp"
#include "../../diff_clock.hpp"
#include "../../enemy_type.hpp"
#include "../../time_delta_fwd.hpp"
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
		sanguis::time_delta const &,
		environment::object &,
		environment::load_context &
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
