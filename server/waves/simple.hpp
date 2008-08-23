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
		time_type spawn_interval,
		unsigned total_spawn_count,
		enemy_type::type);
	void process(
		time_type diff,
		environment const &);
private:
	diff_clock       diff_;
	sge::time::timer spawn_timer;
	unsigned         total_spawn_count;
	enemy_type::type etype;
	unsigned         spawn_count;
};

}
}
}

#endif
