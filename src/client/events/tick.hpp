#ifndef SANGUIS_CLIENT_EVENTS_TICK_HPP_INCLUDED
#define SANGUIS_CLIENT_EVENTS_TICK_HPP_INCLUDED

#include "tick_fwd.hpp"
#include "../../duration.hpp"
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
		sanguis::duration const &
	);

	sanguis::duration const &
	delta() const;
private:
	sanguis::duration const delta_;
};

}
}
}

#endif
