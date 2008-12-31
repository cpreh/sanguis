#ifndef SANGUIS_SERVER_WAVES_SIMPLE_HPP_INCLUDED
#define SANGUIS_SERVER_WAVES_SIMPLE_HPP_INCLUDED

#include "wave.hpp"
#include "../../time_type.hpp"
#include "../../enemy_type.hpp"
#include "../../diff_clock.hpp"
#include <sge/time/timer.hpp>

namespace sanguis
{
namespace server
{

struct environment;

namespace waves
{

class simple : public wave {
public:
	simple(
		time_type delay,
		time_type spawn_interval,
		unsigned waves,
		unsigned spawns_per_wave,
		enemy_type::type);
	void process(
		time_type diff,
		environment const &);
	bool ended() const;
private:
	diff_clock       diff_;
	sge::time::timer delay_timer,
	                 spawn_timer;
	unsigned         waves,
	                 spawns_per_wave;
	enemy_type::type etype;
	unsigned         waves_spawned;
};

}
}
}

#endif
