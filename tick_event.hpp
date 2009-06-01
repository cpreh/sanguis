#ifndef SANGUIS_TICK_EVENT_HPP_INCLUDED
#define SANGUIS_TICK_EVENT_HPP_INCLUDED

#include "tick_event_fwd.hpp"
#include "time_type.hpp"
#include <boost/statechart/event.hpp>

namespace sanguis
{
class tick_event : public boost::statechart::event<tick_event>
{
public:
	explicit tick_event(time_type);
	time_type delta() const;
private:
	time_type delta_;
};

}

#endif
