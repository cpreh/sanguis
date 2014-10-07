#ifndef SANGUIS_SERVER_EVENTS_TICK_HPP_INCLUDED
#define SANGUIS_SERVER_EVENTS_TICK_HPP_INCLUDED

#include <sanguis/duration.hpp>
#include <sanguis/server/slowdown.hpp>
#include <sanguis/server/events/tick_fwd.hpp>
#include <fcppt/nonassignable.hpp>
#include <fcppt/config/external_begin.hpp>
#include <boost/statechart/event.hpp>
#include <fcppt/config/external_end.hpp>


namespace sanguis
{
namespace server
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
	tick(
		sanguis::duration const &,
		sanguis::server::slowdown
	);

	sanguis::duration const &
	delta() const;

	sanguis::server::slowdown const
	slowdown() const;
private:
	sanguis::duration const delta_;

	sanguis::server::slowdown const slowdown_;
};

}
}
}

#endif
