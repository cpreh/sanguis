#ifndef SANGUIS_SERVER_WAVES_SIMPLE_HPP_INCLUDED
#define SANGUIS_SERVER_WAVES_SIMPLE_HPP_INCLUDED

#include "wave.hpp"
#include "delay.hpp"
#include "spawn_interval.hpp"
#include "../environment/load_context_fwd.hpp"
#include "../environment/object_fwd.hpp"
#include "../../enemy_type.hpp"
#include "../../diff_clock_fwd.hpp"
#include "../../diff_timer.hpp"
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
		sanguis::diff_clock const &,
		waves::delay const &,
		waves::spawn_interval const &,
		unsigned waves,
		unsigned spawns_per_wave,
		enemy_type::type
	);

	~simple();
private:
	void
	process(
		environment::object &,
		environment::load_context &
	);

	bool
	ended() const;

	sanguis::diff_clock const &diff_clock_;

	sanguis::diff_timer
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
