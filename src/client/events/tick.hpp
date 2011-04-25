#ifndef SANGUIS_CLIENT_EVENTS_TICK_HPP_INCLUDED
#define SANGUIS_CLIENT_EVENTS_TICK_HPP_INCLUDED

#include "tick_fwd.hpp"
#include "../../time_delta.hpp"
#include <fcppt/nonassignable.hpp>
#include <boost/statechart/event.hpp>

namespace sanguis
{
namespace client
{
namespace events
{

class tick
:
	public boost::statechart::event<
		tick
	>
{
	FCPPT_NONASSIGNABLE(
		tick
	);
public:
	explicit tick(
		sanguis::time_delta const &
	);

	sanguis::time_delta const &
	delta() const;
private:
	sanguis::time_delta const delta_;
};

}
}
}

#endif
