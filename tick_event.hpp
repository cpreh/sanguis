#ifndef SANGUIS_SERVER_TICK_EVENT_HPP_INCLUDED
#define SANGUIS_SERVER_TICK_EVENT_HPP_INCLUDED

#include "data_event.hpp"
#include <sge/timer.hpp>

namespace sanguis
{
struct tick_data 
{
	sge::timer::frames_type diff_time;

	tick_data(const sge::timer::frames_type diff_time) : diff_time(diff_time) {}
};

typedef data_event<tick_data> tick_event;
}

#endif
