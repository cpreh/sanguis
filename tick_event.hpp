#ifndef SANGUIS_SERVER_TICK_EVENT_HPP_INCLUDED
#define SANGUIS_SERVER_TICK_EVENT_HPP_INCLUDED

#include "time_diff.hpp"
#include <boost/statechart/event.hpp>

namespace sanguis
{
class tick_event : public boost::statechart::event<tick_event>
{
	public:
	tick_event(const time_diff);
	time_diff delta() const;

	private:
	time_diff delta_;
};

}

#endif
